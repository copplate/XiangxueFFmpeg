//
// Created by wyc on 2026/6/20.
//

#ifndef FFMPEGPDFXIANGXUE_PLAYER_H
#define FFMPEGPDFXIANGXUE_PLAYER_H

#include "decoder/video/v_decoder.h"
class Player {
private:
    VideoDecoder *m_v_decoder;
    VideoRender *m_v_render;
public:
    Player(JNIEnv *jniEnv, jstring path, jobject surface);

    ~Player();

    void play();

    void pause();
};

#endif //FFMPEGPDFXIANGXUE_PLAYER_H
