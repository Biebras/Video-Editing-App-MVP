#include "video.h"

//Constructor
Video::Video(QString path, int start, int end, int volume)
{
    _pathName = path;
    _start = start;
    _end = end;
    _volume = volume;
}

//Constructor
Video::Video(Video* video)
{
    _pathName = video->GetFilePath();
    _start = video->GetStart();
    _end = video->GetEnd();
    _volume = video->GetVolume();
    _rawDuration = video->GetRawDuration();
}

//returns path of this video
QString Video::GetFilePath()
{
    return _pathName;
}

//sets start of this video in ms
void Video::SetStart(int start)
{
    _start = start;
}

// returns start of this video in ms
int Video::GetStart()
{
    return _start;
}

// set end of this video in ms
void Video::SetEnd(int end)
{
    _end = end;
}

// returns end of this video in ms
int Video::GetEnd()
{
    return _end;
}

// sets raw duration of this video (How long this video is, without ant croping)
void Video::SetRawDuration(int rawDuration)
{
    _rawDuration = rawDuration;
}

// returns raw duration of this video
int Video::GetRawDuration()
{
    return _rawDuration;
}

// sets volume
void Video::SetVolume(int volume)
{
    _volume = volume;
}

// returns volume
int Video::GetVolume()
{
    return _volume;
}

//returns duration between start and end
int Video::GetDuration()
{
    return _end - _start;
}
