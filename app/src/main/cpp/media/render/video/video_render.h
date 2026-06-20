//
// Created by wyc on 2026/6/20.
//

#ifndef FFMPEGPDFXIANGXUE_VIDEO_RENDER_H
#define FFMPEGPDFXIANGXUE_VIDEO_RENDER_H

#include <stdint.h>
#include <jni.h>
#include "../../one_frame.h"
class VideoRender {
public:
    virtual void InitRender(JNIEnv *env, int video_width, int video_height, int *dst_size)
    = 0;
    virtual void Render(OneFrame *one_frame) = 0;
    virtual void ReleaseRender() = 0;
};

#endif //FFMPEGPDFXIANGXUE_VIDEO_RENDER_H
