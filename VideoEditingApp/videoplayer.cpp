#include "videoplayer.h"
#include <QList>
#include <stdlib.h>
#include <QUrl>

// check which video should be playing
void VideoPlayer::Update()
{
    Video* newVideo = _videoManager->GetVideo(_currentTime);
    if (newVideo != _currentVideo)
    {
        // set the video player to show the new video
        this->setMedia(QUrl(QString::fromStdString(newVideo->GetFilePath())));
    }
}

// play the video at the specified milliseconds
void VideoPlayer::Play(int milliseconds)
{
    this->setPosition(milliseconds);
    this->play();
}

// pause the current video
void VideoPlayer::Pause()
{
    this->pause();
}

// get the video at the specified millseconds
Video* VideoPlayer::GetVideo(int milliseconds)
{
    // need to find the video at that time
    return _videoManager->GetVideo(milliseconds);
}

// sets the current time, and makes sure the correct video is playing
void VideoPlayer::SetCurrentTime(int milliseconds)
{
    _currentTime = milliseconds;
    this->Update(); // this will check if the video now needs to be updated
}

int VideoPlayer::GetCurrentTime()
{
    return _currentTime;
}
