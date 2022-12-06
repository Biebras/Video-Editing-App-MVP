#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QList>
#include "video.h"

class VideoManager
{
    private:
        QList<Video*> _videos;
    public:
        VideoManager(string conentPathName);
        ~VideoManager();
        void AddVideo(Video* video);
        void RemoveVideo(Video* video);
        Video* GetVideo(int milliseconds);
};

#endif // VIDEOMANAGER_H
