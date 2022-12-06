#include <iostream>
#include <QDir>
#include <QtCore/QDirIterator>
#include <QString>
#include <QDebug>
#include "videomanager.h"

VideoManager::VideoManager(string conentPathName)
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
        qDebug() << "No videos found, new project or there's something wrong with content path name " << Qt::endl;
    }
}

VideoManager::~VideoManager()
{

}

void VideoManager::AddVideo(Video* video)
{
    _videos.append(video);
}

void VideoManager::RemoveVideo(Video* video)
{
    bool success = _videos.removeOne(video);

    if(!success)
        std::cout << "Couldn't remove video" << std::endl;
}

Video* VideoManager::GetVideo(int milliseconds)
{
    return NULL;
}
