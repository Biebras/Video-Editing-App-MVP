#include "editscene.h"
#include "videogalleryscene.h"
#include "projectsscene.h"
#include "createprojectscene.h"
#include "trimscene.h"
#include "modularlayout.h"
#include "scenemanager.h"

void SceneManager::InitScenes()
{
    _window = new PrimaryWindow();
    _sceneLayout = new ModularLayout();
    _window->centralWidget()->setLayout(_sceneLayout);

    Scene* editScene = new EditScene("edit");
    Scene* videoGalleryScene = new VideoGalleryScene("gallery");
    Scene* projectsScene = new ProjectsScene("projects");
    Scene* createProjectScene = new CreateProjectScene("createProject");
    Scene* trimScene = new TrimScene("trim");

    _scenes.push_back(editScene);
    _scenes.push_back(videoGalleryScene);
    _scenes.push_back(projectsScene);
    _scenes.push_back(createProjectScene);
    _scenes.push_back(trimScene);

    //_window->setLayout(_sceneLayout);

    //load all scenes to scene layout
    foreach(auto scene, _scenes)
    {
        _sceneLayout->addWidget(scene);
    }

    SetScene("projects");
}

void SceneManager::SetScene(QString sceneName)
{
    foreach(auto scene, _scenes)
    {
        if(scene->GetSceneName().compare(sceneName) == 0)
        {
            scene->setVisible(true);
            scene->UpdateScene();
            _currentScene = scene;
        }
        else
            scene->setVisible(false);
    }
}

void SceneManager::UpdateCurrentScene()
{
    if(_currentScene != NULL && _currentScene->GetSceneName() == "gallery")
        _currentScene->UpdateScene();
}

Scene* SceneManager::GetScene(QString sceneName)
{
    foreach(auto scene, _scenes)
    {
         if(scene->GetSceneName().compare(sceneName) == 0)
            return scene;
    }

    qDebug() << "Scene with name " << sceneName << " was not found";
    return NULL;
}

Scene* SceneManager::GetCurrentScene()
{
    return _currentScene;
}

void SceneManager::ShowWindow()
{
        _window->show();
}


PrimaryWindow* SceneManager::GetWindow()
{
    return _window;
}



