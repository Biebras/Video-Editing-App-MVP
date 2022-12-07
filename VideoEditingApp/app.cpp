#include <iostream>
#include <QApplication>
#include "videomanager.h"
#include "editscene.h"

using namespace std;

int main(int argc, char *argv[])
{
    // create the Qt Application
    QApplication app(argc, argv);

    if(argc != 2)
        cout << "There should be two arguments" << endl;

    VideoManager& videoManager = VideoManager::Get();

    videoManager.LoadVideos(argv[1]);
    videoManager.PrintAllVideos();

    QWidget *window = new QWidget();
    EditScene* editScene = new EditScene();

    window->setWindowTitle("App");
    window->setMinimumSize(400, 720);
    window->setLayout(editScene->layout());

    window->show();

    return app.exec();
}
