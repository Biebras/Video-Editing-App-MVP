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

    if(argc != 2)
        cout << "There should be two arguments" << endl;

    VideoManager& videoManager = VideoManager::Get();
    ProjectManager& projectManager = ProjectManager::Get();
    TranslationManager& translationManager = TranslationManager::Get();

    //set up translation
    QTranslator translator;

    translationManager.InitTranslation(translator);

    projectManager.LoadProjects(argv[1]);

    SceneManager& sceneManager = SceneManager::Get(); // initialise the scene manager
    sceneManager.InitScenes();

    sceneManager.ShowWindow();

    return app.exec();
}
