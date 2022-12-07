#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QList>
#include "video.h"

class VideoManager
{
    public:
        VideoManager(const VideoManager&) = delete;

        static VideoManager& Get()
        {
            static VideoManager instance;
            return instance;
        };
        void LoadVideos(string conentPathName);
        ~VideoManager();
        void AddVideo(Video* video);
        void RemoveVideo(Video* video);
        Video* GetVideo(int milliseconds);
        void PrintAllVideos();
    private:
        VideoManager(){}

        QList<Video*> _videos;
};

#endif // VIDEOMANAGER_H
