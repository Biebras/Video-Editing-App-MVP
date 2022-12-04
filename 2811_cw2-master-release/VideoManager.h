#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QList>
#include "Video.h"

class VideoManager
{
    private:
        QList<Video*> _videos;
    public:
        VideoManager();
};

#endif // VIDEOMANAGER_H
