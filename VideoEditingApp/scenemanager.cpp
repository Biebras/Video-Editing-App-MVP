#include "editscene.h"
#include "videogalleryscene.h"
#include "projectsscene.h"
#include "createprojectscene.h"
#include "trimscene.h"
#include "modularlayout.h"
#include "scenemanager.h"

//initiate all scenes and puts them in the list
void SceneManager::InitScenes()
{
    //creates primary window
    _window = new PrimaryWindow();
    _sceneLayout = new ModularLayout();
    _window->centralWidget()->setLayout(_sceneLayout);
    _sceneLayout->setSpacing(0);
    _sceneLayout->setMargin(0);

    //creates all the scenes
    Scene* editScene = new EditScene("edit");
    Scene* videoGalleryScene = new VideoGalleryScene("gallery");
    Scene* projectsScene = new ProjectsScene("projects");
    Scene* createProjectScene = new CreateProjectScene("createProject");
    Scene* trimScene = new TrimScene("trim");

    //puts all the scenes to the list
    _scenes.push_back(editScene);
    _scenes.push_back(videoGalleryScene);
    _scenes.push_back(projectsScene);
    _scenes.push_back(createProjectScene);
    _scenes.push_back(trimScene);

    //load all scenes to scene layout
    foreach(auto scene, _scenes)
    {
        _sceneLayout->addWidget(scene);
    }

    //set default scene
    SetScene("projects");
}

// Set scene to spesified name, shows it and updates it
void SceneManager::SetScene(QString sceneName)
{
    //loop through all scenes
    foreach(auto scene, _scenes)
    {
        //if scene name was found set is as current scene
        if(scene->GetSceneName().compare(sceneName) == 0)
        {
            scene->setVisible(true);
            scene->UpdateScene();
            _currentScene = scene;
        }
        else
            //hide all the other scnenes
            scene->setVisible(false);
    }
}

//updatescurrent scene
void SceneManager::UpdateCurrentScene()
{
    if(_currentScene != NULL && _currentScene->GetSceneName() == "gallery")
        _currentScene->UpdateScene();
}

//retranslates all scenes
void SceneManager::RetranslateScenes()
{
    foreach(auto scene, _scenes)
    {
        scene->Retranslate();
    }
}

// returns scene by name
Scene* SceneManager::GetScene(QString sceneName)
{
    //loop through all scnes and retrieve scne
    foreach(auto scene, _scenes)
    {
         if(scene->GetSceneName().compare(sceneName) == 0)
            return scene;
    }

    //if no scene was found with name, return null
    qDebug() << "Scene with name " << sceneName << " was not found";
    return NULL;
}

//return current scene
Scene* SceneManager::GetCurrentScene()
{
    return _currentScene;
}

// show main window
void SceneManager::ShowWindow()
{
        _window->show();
}

// returns main window
PrimaryWindow* SceneManager::GetWindow()
{
    return _window;
}



