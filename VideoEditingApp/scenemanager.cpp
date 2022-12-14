#include "scenemanager.h"
#include "editscene.h"
#include "videogalleryscene.h"
#include "projectsscene.h"
#include "createprojectscene.h"
#include "trimscene.h"
#include "modularlayout.h"

QWidget* SceneManager::GetWindow()
{
    return _window;
}

void SceneManager::InitScenes()
{
    _window = new QWidget();

    _window->setWindowTitle("App");
    _window->setMinimumSize(400, 720);
    _window->resize(_window->minimumSize());

    _sceneLayout = new ModularLayout();

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

    _window->setLayout(_sceneLayout);

    //load all scenes to scene layout
    foreach(auto scene, _scenes)
    {
        _sceneLayout->addWidget(scene);
    }

    SetScene("edit");
}

void SceneManager::SetScene(QString sceneName)
{
    foreach(auto scene, _scenes)
    {
        if(scene->GetSceneName().compare(sceneName) == 0)
        {
            scene->setVisible(true);
            _currentScene = scene;
        }
        else
            scene->setVisible(false);
    }
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


