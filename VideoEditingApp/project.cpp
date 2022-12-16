#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QString>
#include "project.h"

using namespace std;

// Constructor
Project::Project(QString path, QString name)
{
    _pathName = path;
    _projectName = name;
}

// Deconstructor
Project::~Project()
{
    qDeleteAll(_videos);
    _videos.clear();
}

// Loads all videos in the project
void Project::LoadProjectVideos()
{
    // Delete the current project
    _videos.clear();

    //Create access to directory's contetedit
    QDir dir (_pathName);
    //Create itirator to iterate directories
    QDirIterator itirator(dir);

    //iterate through projects content
    while(itirator.hasNext())
    {
        QString pathName = itirator.next();

#if defined(_WIN32)
        // windows
        if (pathName.contains(".wmv"))
        {
#else
        // mac/linux
        if (pathName.contains(".mp4") || pathName.contains("MOV"))
        {
#endif

            //Create new video with volume 1
            Video* video = new Video(pathName, 0, 0, 1);
            AddVideo(video);
        }
    }

    //if no videos were loaded, notifie
    if(_videos.count() == 0)
    {
        qDebug() << "No videos found, new project or there's something wrong with content path name ";
    }
}

//Returns project path
QString Project::GetProjectPath()
{
    return _pathName;
}

//Returns project name
QString Project::GetProjectName()
{
    return _projectName;
}

// Retirms videos list
QList<Video*> Project::GetVideos()
{
    return _videos;
}

// adds video to the list
void Project::AddVideo(Video* video)
{
    _videos.append(video);
}

// removes video from the list
void Project::RemoveVideo(Video* video)
{
    bool success = _videos.removeOne(video);

    if(!success)
        qDebug() << "Couldn't remove video";
}

// returns video with spesified index, if index invalid, returns NULL
Video* Project::GetVideo(int index)
{
    if (index < GetTotalVideos() && index > -1)
        return _videos[index];

    qDebug() <<  "Couldn't retrieve video at index: " << index;
    return NULL;
}

//Prints all loaded videos in this project
void Project::PrintAllVideos()
{
    qDebug() << "Printing videos";
    qDebug() << "==========================================";
    for(auto video : _videos)
    {
        qDebug()  << "Path: " << video->GetFilePath();

        qDebug()  << "==========================================" ;
    }
}

//returns total count of videos in this project
int Project::GetTotalVideos()
{
    return _videos.size();
}
