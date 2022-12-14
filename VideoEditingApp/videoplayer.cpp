#include "videoplayer.h"
#include "videomanager.h"
#include "video.h"
#include <QList>
#include <stdlib.h>
#include <QUrl>

// check which video should be playing
void VideoPlayer::Update()
{
    // if at the end of last video, play first video
    if (_currentTime >= _videoManager->GetTotalDuration())
    {
        setMedia(QUrl(QUrl::fromLocalFile(_videoManager->GetVideo(0)->GetFilePath())));
        SetCurrentVideo(_videoManager->GetVideo(0));
        SetCurrentTime(0);
        return;
    }

    // check if video at current time is the one playing, if not set it to be
    Video* newVideo = _videoManager->GetVideoByMS(_currentTime+1);
    if (newVideo != _currentVideo)
    {
        // set the video player to show the new video
        this->setMedia(QUrl(QUrl::fromLocalFile(newVideo->GetFilePath())));
        SetCurrentVideo(newVideo);
        SetCurrentTime(newVideo->GetStart());
    }
}

// play the video at the specified milliseconds
void VideoPlayer::Play(int milliseconds)
{
    // calculate the position of the current video in the player
    int actual = milliseconds - _currentVideo->GetStart();

    this->setPosition(actual);
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
    return _videoManager->GetVideoByMS(milliseconds);
}

// sets the current time, and makes sure the correct video is playing
void VideoPlayer::SetCurrentTime(int milliseconds)
{
    _currentTime = milliseconds;
//    this->Update(); // this will check if the video now needs to be updated
}

int VideoPlayer::GetCurrentTime2()
{
    return _currentTime;
}

void VideoPlayer::SetCurrentVideo(Video* video)
{
    _currentVideo = video;
}

Video* VideoPlayer::GetCurrentVideo()
{
    return _currentVideo;
}
