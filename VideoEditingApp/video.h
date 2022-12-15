#ifndef VIDEO_H
#define VIDEO_H

#include <QString>

using namespace std;

class Video
{
    private:
        QString _pathName;
        int _start = 0;
        int _end = 0;
        int _rawDuration = 0;
        int _volume = 1;

    public:
        Video(Video* video);
        Video(QString path, int start, int end, int volume);
        QString GetFilePath();
        void SetStart(int start);
        int GetStart();
        void SetEnd(int end);
        int GetEnd();
        void SetRawDuration(int rawDuration);
        int GetRawDuration();
        void SetVolume(int volume);
        int GetVolume();
        int GetDuration();
};

#endif // VIDEO_H
