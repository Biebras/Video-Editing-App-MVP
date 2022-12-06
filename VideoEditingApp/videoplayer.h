#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMediaPlayer>
#include "video.h"
#include "videomanager.h"


class VideoPlayer : public QMediaPlayer
{
    public:
        VideoPlayer() : QMediaPlayer(NULL) {};
        void Update();
        void Play(int millisecond);
        void Pause();
        Video* GetVideo(int milliseconds);
        void SetCurrentTime(int milliseconds);
        int GetCurrentTime();


    private:
        int _currentTime;
        Video* _currentVideo;
        VideoManager* _videoManager;
};

#endif // VIDEOPLAYER_H