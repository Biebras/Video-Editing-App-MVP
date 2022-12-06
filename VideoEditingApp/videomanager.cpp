#include <iostream>
#include "videomanager.h"

VideoManager::VideoManager()
{

}

void VideoManager::AddVideo(Video* video)
{
    _videos.append(video);
}

void VideoManager::RemoveVideo(Video* video)
{
    bool success = _videos.removeOne(video);

    if(!success)
        std::cout << "Couldn't remove video" << std::endl;
}

Video* VideoManager::GetVideo(int milliseconds)
{
    return NULL;
}
