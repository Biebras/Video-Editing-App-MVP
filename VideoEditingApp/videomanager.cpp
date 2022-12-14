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

void VideoManager::LoadVideos(QString loadFilePath)
{
    ClearVideos();

    QString jsonFilePath = loadFilePath + "/save.json";
    QFile file(jsonFilePath);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "File open error";
        return;
    }

    qDebug() << "Successfully opened file";

    QByteArray bytes = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError);

    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << "json failed: " << jsonError.errorString();
        return;
    }

    QJsonArray jsonArray = document.array();

    foreach(const QJsonValue & value, jsonArray)
    {
        QJsonObject object = value.toObject();

        QString pathName = object.value("pathName").toString();
        int start = object.value("start").toInt();
        int end = object.value("end").toInt();
        int rawDuration = object.value("rawDuration").toInt();
        int volume = object.value("volume").toInt();

        Video* video = new Video(pathName, start, end, volume);
        video->SetRawDuration(rawDuration);
        AddVideo(video);
    }

     qDebug() << "Successfully loaded files";
}

void VideoManager::SaveVideos(QString saveFilePath)
{
    QString jsonFilePath = saveFilePath + "/save.json";
    QFile file(jsonFilePath);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        qDebug() << "File open error";
        return;
    }

    qDebug() << "Successfully opened file";

    QJsonObject obj;
    QJsonArray jsonArray;

    foreach(auto video, _videos)
    {
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
    QByteArray bytes = document.toJson(QJsonDocument::Indented);

    QTextStream stream(&file);
    stream.setCodec("utf-8");
    stream << bytes;
    file.close();
     qDebug() << "Successfully saved video data";
}

void VideoManager::ClearVideos()
{
    qDeleteAll(_videos);
    _videos.clear();
}

VideoManager::~VideoManager()
{
    qDeleteAll(_videos);
    _videos.clear();
}

void VideoManager::AddVideo(Video* video)
{
    _videos.push_back(video);
}

void VideoManager::RemoveVideo(Video* video)
{
    bool success = _videos.removeOne(video);

    if(!success)
        cout << "Couldn't remove video" << endl;
}

Video* VideoManager::GetVideoByMS(int milliseconds)
{
    foreach(auto video, _videos)
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

int VideoManager::GetTotalVideos()
{
    return _videos.size();
}

void VideoManager::InsertVideo(int index, Video* video)
{
    _videos.insert(index, video);
}

int VideoManager::GetTotalDuration()
{
    int total = 0;
    for (auto video : _videos)
    {
        total += video->GetDuration();
    }
    return total;
}
