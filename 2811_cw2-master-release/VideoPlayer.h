#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMediaPlayer>
#include "Video.h"
#include "videomanager.h"


class VideoPlayer : public QMediaPlayer
{
    public:
        VideoPlayer();
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
