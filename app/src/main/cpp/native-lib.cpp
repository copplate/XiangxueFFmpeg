#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <android/log.h>

// ========= 关键修改：用 extern "C" 包裹 C 语言库的头文件 =========
extern "C" {
#include "ffmpeg/include/libavcodec/avcodec.h"
#include "ffmpeg/include/libavutil/avutil.h"
}
// ============================================================

#define LOG_TAG "FFmpegNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void checkLibraryLocation();

extern "C" JNIEXPORT jstring JNICALL
Java_com_wwyc_ffmpegpdfxiangxue_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    checkLibraryLocation();
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

// 在某个函数中
void checkLibraryLocation() {
    Dl_info info;
    if (dladdr((void*)checkLibraryLocation, &info)) {
        __android_log_print(ANDROID_LOG_DEBUG, "tiktok",
                            "Library loaded from: %s", info.dli_fname);
    }
}

extern "C" {

JNIEXPORT jstring JNICALL
Java_com_wwyc_ffmpegpdfxiangxue_MainActivity_ffmpegInfo(JNIEnv *env, jobject /* this */)
{
    std::string result;
    result.reserve(40000); // 预分配空间以提高性能

    // 使用 av_codec_iterate 替代已废弃的 av_codec_next
    const AVCodec *codec = NULL;
    void *iter = NULL;

    // 首先注册所有编解码器（FFmpeg 4.0+ 可能需要）
    // avcodec_register_all(); // 在新版本中可能已废弃

    int count = 0;

    // 遍历所有编解码器
    while ((codec = av_codec_iterate(&iter))) {
        const char *type_str;
        const char *codec_type;

        // 判断编解码器类型（解码器或编码器）
        if (av_codec_is_decoder(codec)) {
            codec_type = "decode";
        } else if (av_codec_is_encoder(codec)) {
            codec_type = "encode";
        } else {
            codec_type = "unknown";
        }

        // 判断媒体类型
        switch (codec->type) {
            case AVMEDIA_TYPE_VIDEO:
                type_str = "video";
                break;
            case AVMEDIA_TYPE_AUDIO:
                type_str = "audio";
                break;
            case AVMEDIA_TYPE_SUBTITLE:
                type_str = "subtitle";
                break;
            default:
                type_str = "other";
                break;
        }

        // 拼接信息
        char line[256];
        snprintf(line, sizeof(line), "[%s][%s] %-20s %s\n",
                 codec_type, type_str, codec->name,
                 codec->long_name ? codec->long_name : "");

        result += line;
        count++;

        // 防止结果过长
        if (result.length() > 35000) {
            result += "... (truncated)";
            break;
        }
    }

    LOGI("Total codecs found: %d", count);

    if (result.empty()) {
        result = "No codecs found!";
        LOGE("Failed to get codec information");
    }

    return env->NewStringUTF(result.c_str());
}

} // extern "C"