#include <iostream>
#include <QApplication>
#include "videomanager.h"

using namespace std;

int main(int argc, char *argv[])
{
    // create the Qt Application
    QApplication app(argc, argv);

    if(argc != 2)
        cout << "There should be two arguments" << endl;

    VideoManager* videoManager = new VideoManager(argv[1]);

    videoManager->PrintAllVideos();

    return app.exec();
}
