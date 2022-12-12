#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <string>
#include "video.h"

using namespace std;

class Project
{
    public:
        Project(string pathName);
        string GetProjectPath();
        string GetProjectName();
        void AddVideo(Video* video);
        void RemoveVideo(Video* video);
        Video* GetVideo(int index);
        void PrintAllVideos();
        int GetTotalVideos();

    private:
        string _projectName;
        string _pathName;
        QList<Video*> _videos;
};

#endif // PROJECT_H
