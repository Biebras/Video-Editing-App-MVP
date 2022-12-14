#include "video.h"

Video::Video(QString path, int start, int end, int volume)
{
    _pathName = path;
    _start = start;
    _end = end;
    _volume = volume;
}

QString Video::GetFilePath()
{
    return _pathName;
}

void Video::SetStart(int start)
{
    _start = start;
}

int Video::GetStart()
{
    return _start;
}

void Video::SetEnd(int end)
{
    _end = end;
}

int Video::GetEnd()
{
    return _end;
}

void Video::SetRawDuration(int rawDuration)
{
    _rawDuration = rawDuration;
}

int Video::GetRawDuration()
{
    return _rawDuration;
}

void Video::SetVolume(int volume)
{
    _volume = volume;
}

int Video::GetVolume()
{
    return _volume;
}

int Video::GetDuration()
{
    return _end - _start;
}
