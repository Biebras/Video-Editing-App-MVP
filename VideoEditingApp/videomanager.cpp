#include <QJsonParseError>
#include <QTextStream>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>
#include <QDir>
#include <QtCore/QDirIterator>
#include <QFile>
#include <QString>
#include "videomanager.h"
#include "videoplayer.h"
#include <QDebug>
#include <QUrl>

using namespace std;

// Load videos from save file.
void VideoManager::LoadVideos(QString loadFilePath)
{
    //Clear all videos
    ClearVideos();

    // set save path
    QString jsonFilePath = loadFilePath + "/save.json";
    QFile file(jsonFilePath);

    //if can't open the file, return
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "File open error";
        return;
    }

    qDebug() << "Successfully opened file";
    //read bytes from file and close it
    QByteArray bytes = file.readAll();
    file.close();

    QJsonParseError jsonError;
    //convert to document to manipulate data
    QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError);

    //if json is invalid, return
    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << "json failed: " << jsonError.errorString();
        return;
    }

    //get videos data  array
    QJsonArray jsonArray = document.array();

    //loop through data array
    foreach(const QJsonValue & value, jsonArray)
    {
        //convert value to object
        QJsonObject object = value.toObject();

        // retrieve information
        QString pathName = object.value("pathName").toString();
        int start = object.value("start").toInt();
        int end = object.value("end").toInt();
        int rawDuration = object.value("rawDuration").toInt();
        int volume = object.value("volume").toInt();

        //create video from that information
        Video* video = new Video(pathName, start, end, volume);
        video->SetRawDuration(rawDuration);
        AddVideo(video);
    }

     qDebug() << "Successfully loaded files";
}

// saves video information to json file
void VideoManager::SaveVideos(QString saveFilePath)
{
    //set json file path
    QString jsonFilePath = saveFilePath + "/save.json";
    QFile file(jsonFilePath);

    //try to open file, if can't return. If file do not exist, creates one.
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        qDebug() << "File open error";
        return;
    }

    qDebug() << "Successfully opened file";

    QJsonObject obj;
    QJsonArray jsonArray;

    //loop through videos
    foreach(auto video, _videos)
    {
        //fort each video create json object
        QJsonObject jsonVideo = QJsonObject(
        {
            qMakePair(QString("pathName"), QJsonValue(video->GetFilePath())),
            qMakePair(QString("start"), QJsonValue(video->GetStart())),
            qMakePair(QString("end"), QJsonValue(video->GetEnd())),
            qMakePair(QString("rawDuration"), QJsonValue(video->GetRawDuration())),
            qMakePair(QString("volume"), QJsonValue(video->GetVolume())),
        });

        jsonArray.push_back(jsonVideo);
    }

    QJsonDocument document;
    document.setArray(jsonArray);
    //get bytes
    QByteArray bytes = document.toJson(QJsonDocument::Indented);

    // input data to json file
    QTextStream stream(&file);
    stream.setCodec("utf-8");
    stream << bytes;
    file.close();
     qDebug() << "Successfully saved video data";
}

//clear all videos
void VideoManager::ClearVideos()
{
    qDeleteAll(_videos);
    _videos.clear();
}

//deconstructor
VideoManager::~VideoManager()
{
    qDeleteAll(_videos);
    _videos.clear();
}

//create copy of video and add to the video list (we copy so we can have duplicate videos in editor)
void VideoManager::AddVideo(Video* video)
{
    Video* newVideo = new Video(video);
    _videos.push_back(newVideo);
}

//remove video
void VideoManager::RemoveVideo(Video* video)
{
    bool success = _videos.removeOne(video);

    if(!success)
        cout << "Couldn't remove video" << endl;
}

//returns video in spesified time step, if no video is found return NULL
Video* VideoManager::GetVideoByMS(int milliseconds)
{
    //loop through all videos and check if they fall in timestep
    foreach(auto video, _videos)
    {
        if(milliseconds >= video->GetStart() && milliseconds <= video->GetEnd())
            return video;
    }

    cout << "Could't retvieve video within " << milliseconds << "ms" << endl;
    return NULL;
}

// return video with spesified index, if index is invalid return NULL
Video* VideoManager::GetVideo(int index)
{
    if (index < GetTotalVideos() && index > -1)
        return _videos[index];

    cout << "Couldn't retrieve video at index " << index << endl;
    return NULL;
}

// return all videos
void VideoManager::PrintAllVideos()
{
    qDebug() << "Printing videos";
    qDebug() << "==========================================";

    foreach(auto video, _videos)
    {
        qDebug() << "Path: " << video->GetFilePath();
        qDebug() << "Start: " << video->GetStart();
        qDebug() << "End: " << video->GetEnd();
        qDebug() << "Volume: " << video->GetVolume();
        qDebug() << "Duration: " << video->GetDuration();
        qDebug() << "Raw Duration: " << video->GetRawDuration();
        qDebug() << "==========================================";
    }
}

// return videos count
int VideoManager::GetTotalVideos()
{
    return _videos.size();
}

//inserts a video into list, without copying it
void VideoManager::InsertVideo(int index, Video* video)
{
    _videos.insert(index, video);
}

// returns total duration
int VideoManager::GetTotalDuration()
{
    int total = 0;
    for (auto video : _videos)
    {
        total += video->GetDuration();
    }
    return total;
}
