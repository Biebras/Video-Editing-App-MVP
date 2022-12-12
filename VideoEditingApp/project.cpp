#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QString>
#include <string>
#include "project.h"

using namespace std;

Project::Project(string path, string name)
{
    _pathName = path;
    _projectName = name;
}

Project::~Project()
{
    qDeleteAll(_videos);
    _videos.clear();
}

void Project::LoadProjectVideos()
{
    //Create access to directory's contet
    QDir dir (QString::fromStdString(_pathName));
    //Create itirator to iterate directories
    QDirIterator itirator(dir);

    while(itirator.hasNext())
    {
        QString pathName = itirator.next();

        if(pathName.contains(".mp4") || pathName.contains("MOV"))
        {
            Video* video = new Video(pathName.toStdString(), 0, 0, 1);
            AddVideo(video);
        }
    }

    if(_videos.count() == 0)
    {
        qDebug() << "No videos found, new project or there's something wrong with content path name ";
    }
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
