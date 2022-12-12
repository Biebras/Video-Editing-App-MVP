#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "qwidget.h"

class SceneManager
{
    public:

        SceneManager(QWidget* const window)
        {
            _window = window;
        };

        static SceneManager& Get(QWidget* const window)
        {
            static SceneManager instance(window);
            return instance;
        }

        QWidget* GetWindow();

    private:
        QWidget* _window;
};

#endif // SCENEMANAGER_H
