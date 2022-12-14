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
        void LoadVideos(QString loadFilePath);
        void SaveVideos(QString saveFilePathName);
        ~VideoManager();
        void AddVideo(Video* video);
        void RemoveVideo(Video* video);
        Video* GetVideoByMS(int milliseconds);
        Video* GetVideo(int index);
        void PrintAllVideos();
        int GetTotalVideos();
        void InsertVideo(int index, Video* video);
        int GetTotalDuration();
    private:
        void ClearVideos();
        VideoManager(){}
        QList<Video*> _videos;
};

#endif // VIDEOMANAGER_H
