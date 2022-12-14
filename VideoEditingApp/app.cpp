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
//    projectManager.SetCurrentProject(projectManager.GetProjectByName("Project1"));
//    Project* currentProject = projectManager.GetCurrentProject();

//    foreach(auto video, currentProject->GetVideos())
//    {
//        videoManager.AddVideo(video);
//    }

    SceneManager& sceneManager = SceneManager::Get(); // initialise the scene manager
    sceneManager.InitScenes();


    sceneManager.ShowWindow();

    return app.exec();
}
