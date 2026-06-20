//
// Created by wyc on 2026/6/19.
//

#ifndef FFMPEGPDFXIANGXUE_I_DECODER_H
#define FFMPEGPDFXIANGXUE_I_DECODER_H
class IDecoder {
public:
    virtual void GoOn() = 0;
    virtual void Pause() = 0;
    virtual void Stop() = 0;
    virtual bool IsRunning() = 0;
    virtual long GetDuration() = 0;
    virtual long GetCurPos() = 0;
};
#endif //FFMPEGPDFXIANGXUE_I_DECODER_H
