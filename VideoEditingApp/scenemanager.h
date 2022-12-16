#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "qwidget.h"
#include "scene.h"
#include "modularlayout.h"
#include "primarywindow.h"

class SceneManager
{
    public:
        SceneManager(const SceneManager&) = delete;

        static SceneManager& Get()
        {
            static SceneManager instance;
            return instance;
        };

        void InitScenes();
        void SetScene(QString sceneName);
        Scene* GetScene(QString sceneName);
        Scene* GetCurrentScene();
        void UpdateCurrentScene();
        void RetranslateScenes();
        void ShowWindow();
        PrimaryWindow* GetWindow();

    private:
        SceneManager(){};

        QList<Scene*> _scenes;
        Scene*_currentScene;
        ModularLayout* _sceneLayout;
        PrimaryWindow* _window;
};

#endif // SCENEMANAGER_H
