#ifndef VIDEO_H
#define VIDEO_H

#import <string>

using namespace std;

class Video
{
    private:
        string _pathName;
        int _start;
        int _end;
        int _volume;
    public:
        Video(string path, int start, int end, int volume);
        string GetFilePath();
        void SetStart(int start);
        int GetStart();
        void SetEnd(int end);
        int GetEnd();
        void SetVolume();
        int GetVolume();
};

#endif // VIDEO_H
