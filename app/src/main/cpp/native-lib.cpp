#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <android/log.h>

void checkLibraryLocation();

extern "C" JNIEXPORT jstring JNICALL
//void checkLibraryLocation();

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