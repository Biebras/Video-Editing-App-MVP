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
#include "translationmanager.h"
#include <QtWidgets>

using namespace std;

int main(int argc, char *argv[])
{
    // create the Qt Application
    QApplication app(argc, argv);

    // check for correct number of args, return error if incorrect
    if(argc != 2)
        cout << "There should be two arguments" << endl;

    // initialise the video, project and translation manager
    VideoManager& videoManager = VideoManager::Get();
    ProjectManager& projectManager = ProjectManager::Get();
    TranslationManager& translationManager = TranslationManager::Get();

    //set up translation
    QTranslator translator;

    translationManager.InitTranslation(translator);

    // load the projects in the file provided in argv[1]
    projectManager.LoadProjects(argv[1]);

    // initialise the scene manager and the scenes
    SceneManager& sceneManager = SceneManager::Get();
    sceneManager.InitScenes();

    // show the window
    sceneManager.ShowWindow();

    return app.exec();
}
