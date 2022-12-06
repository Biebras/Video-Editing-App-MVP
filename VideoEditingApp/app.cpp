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

    QWidget *window = new QWidget();
    //VideoManager* videoManager = new VideoManager(argv[1]);
    EditScene* editScene = new EditScene();

    window->setWindowTitle("App");
    window->setMinimumSize(400, 720);
    window->setLayout(editScene->layout());

    window->show();

    return app.exec();
}
