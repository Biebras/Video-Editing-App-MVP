#include "project.h"

#include <QDebug>
#include <QString>
#include <string>

using namespace std;

Project::Project(string path)
{
    _pathName = path;
}

string Project::GetProjectPath()
{
    return _pathName;
}

string Project::GetProjectName()
{
    return _projectName;
}

void Project::AddVideo(Video* video)
{
    _videos.append(video);
}

void Project::RemoveVideo(Video* video)
{
    bool success = _videos.removeOne(video);

    if(!success)
        qDebug() << "Couldn't remove video";
}

Video* Project::GetVideo(int index)
{
    if (index < GetTotalVideos() && index > -1)
        return _videos[index];

    qDebug() <<  "Couldn't retrieve video at index: " << index;
    return NULL;
}

void Project::PrintAllVideos()
{
    qDebug() << "Printing videos";
    qDebug() << "==========================================";
    for(auto video : _videos)
    {

        qDebug()  << "Path: " << QString::fromStdString(video->GetFilePath());

        qDebug()  << "==========================================" ;
    }
}

int Project::GetTotalVideos()
{
    return _videos.size();
}
