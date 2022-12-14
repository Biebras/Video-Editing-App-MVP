#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include "video.h"

using namespace std;

class Project
{
    public:
        Project(QString path, QString name);
        ~Project();
        void LoadProjectVideos();
        QString GetProjectPath();
        QString GetProjectName();
        void AddVideo(Video* video);
        void RemoveVideo(Video* video);
        Video* GetVideo(int index);
        QList<Video*> GetVideos();
        void PrintAllVideos();
        int GetTotalVideos();

    private:
        QString _projectName;
        QString _pathName;
        QList<Video*> _videos;
};

#endif // PROJECT_H
