#include <iostream>
#include <QDir>
#include <QtCore/QDirIterator>
#include <QString>
#include "videomanager.h"
#include "qdebug.h"

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
    if (index < GetTotalVideos() && index > 0)
        return _videos[index];

    cout << "Couldn't retrieve video at index " << index << endl;
    return NULL;
}

void VideoManager::PrintAllVideos()
{
    cout << "Printing videos" << endl;
    cout << "==========================================" << endl;
    for(auto video : _videos)
    {
        //qDebug() << video->GetFilePath();
        qDebug() << video->GetStart();
        qDebug() << video->GetEnd();
        qDebug() << video->GetVolume();
        qDebug() << video->GetDuration();


        cout << "Path: " << video->GetFilePath() << endl;
        cout << "Start: " << video->GetStart() << endl;
        cout << "End: " << video->GetEnd() << endl;
        cout << "Volume: " << video->GetVolume() << endl;
        cout << "Duration: " << video->GetDuration() << endl;
        cout << "==========================================" << endl;
    }
}

int VideoManager::GetTotalVideos()
{
    return _videos.size();
}
