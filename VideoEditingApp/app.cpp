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

    VideoManager& videoManager = VideoManager::Get();
    ProjectManager& projectManager = ProjectManager::Get();

    projectManager.LoadProjects(argv[1]);
    Project* currentProject = projectManager.GetProject(0);
    projectManager.SetCurrentProject(currentProject);
    videoManager.LoadVideos(currentProject->GetProjectPath());
    //videoManager.SaveVideos(currentProject->GetProjectPath());
    videoManager.PrintAllVideos();

    QWidget *window = new QWidget();

    window->setWindowTitle("App");
    window->setMinimumSize(400, 720);
    window->resize(window->minimumSize());

    SceneManager& sceneManager = SceneManager::Get(window); // initialise the scene manager

    EditScene* editScene = new EditScene();
//    VideoGalleryScene* videoGalleryScene = new VideoGalleryScene();
    //ProjectsScene* projectsScene = new ProjectsScene();
    //CreateProjectScene* createProjectScene = new CreateProjectScene();
//    TrimScene* trimScene = new TrimScene();

    window->setLayout(editScene->layout());
//    window->setLayout(videoGalleryScene->layout());
    //window->setLayout(projectsScene->layout());
   // window->setLayout(createProjectScene->layout());
//    window->setLayout(trimScene->layout());

    window->show();

    return app.exec();
}
