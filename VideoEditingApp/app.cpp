#include <iostream>
#include <QApplication>
#include "videomanager.h"
#include "editscene.h"
#include "videogalleryscene.h"
#include "projectsscene.h"
#include "createprojectscene.h"
#include "trimscene.h"
#include "scenemanager.h"
#include "projectmanager.h"

using namespace std;

int main(int argc, char *argv[])
{
    // create the Qt Application
    QApplication app(argc, argv);

    if(argc != 2)
        cout << "There should be two arguments" << endl;

    QTranslator myappTranslator;
    qDebug() << QApplication::applicationDirPath();
    auto smth = myappTranslator.load(":languages/translation_en.qm");
    qDebug() << smth;
    app.installTranslator(&myappTranslator);

    VideoManager& videoManager = VideoManager::Get();
    ProjectManager& projectManager = ProjectManager::Get();

    projectManager.LoadProjects(argv[1]);

    SceneManager& sceneManager = SceneManager::Get(); // initialise the scene manager
    sceneManager.InitScenes();

    sceneManager.ShowWindow();

    return app.exec();
}
