#include <iostream>
#include <QDir>
#include <QtCore/QDirIterator>
#include <QString>
#include "videomanager.h"
#include <QDebug>

using namespace std;

void VideoManager::LoadVideos(string conentPathName)
{
    //Create access to directory's contet
    QDir dir (QString::fromStdString(conentPathName));
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
        cout << "No videos found, new project or there's something wrong with content path name " << endl;
    }
}

VideoManager::~VideoManager()
{
    qDeleteAll(_videos);
    _videos.clear();
}

void VideoManager::AddVideo(Video* video)
{
    _videos.append(video);
}

void VideoManager::RemoveVideo(Video* video)
{
    bool success = _videos.removeOne(video);

    if(!success)
        cout << "Couldn't remove video" << endl;
}

Video* VideoManager::GetVideoByMS(int milliseconds)
{
    for(auto video : _videos)
    {
        if(milliseconds >= video->GetStart() && milliseconds <= video->GetEnd())
            return video;
    }

    cout << "Could't retvieve video within " << milliseconds << "ms" << endl;
    return NULL;
}

Video* VideoManager::GetVideo(int index)
{
    if (index < GetTotalVideos() && index > -1)
        return _videos[index];

    cout << "Couldn't retrieve video at index " << index << endl;
    return NULL;
}

void VideoManager::PrintAllVideos()
{
    qDebug() << "Printing videos";
    qDebug() << "==========================================";
    for(auto video : _videos)
    {
        qDebug() << "Path: " << QString::fromStdString(video->GetFilePath());
        qDebug() << "Start: " << video->GetStart();
        qDebug() << "End: " << video->GetEnd();
        qDebug() << "Volume: " << video->GetVolume();
        qDebug() << "Duration: " << video->GetDuration();
        qDebug() << "==========================================";

    }
}

int VideoManager::GetTotalVideos()
{
    return _videos.size();
}

void VideoManager::InsertVideo(int index, Video* video)
{
    _videos.insert(index, video);
}
