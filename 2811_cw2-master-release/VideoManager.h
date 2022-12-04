#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QList>
#include "video.h"

class VideoManager
{
    private:
        QList<Video*> _videos;
    public:
        VideoManager();
        ~VideoManager();
        void AddVideo(Video* video);

};

#endif // VIDEOMANAGER_H
