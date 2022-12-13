#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "qwidget.h"
#include "scene.h"
#include "modularlayout.h"

class SceneManager
{
    public:
        SceneManager(const SceneManager&) = delete;

        static SceneManager& Get()
        {
            static SceneManager instance;
            return instance;
        };

        QWidget* GetWindow();
        void InitScenes();
        void SetScene(QString sceneName);
        Scene* GetScene(QString sceneName);
        Scene* GetCurrentScene();
        void ShowWindow();

    private:
        SceneManager(){};

        QWidget* _window;
        QList<Scene*> _scenes;
        Scene*_currentScene;
        ModularLayout* _sceneLayout;
};

#endif // SCENEMANAGER_H
