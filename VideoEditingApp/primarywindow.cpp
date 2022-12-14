#include "primarywindow.h"
#include <QDebug>
#include "scenemanager.h"

PrimaryWindow::PrimaryWindow()
{
    //set window background colour
    setWindowTitle("App");
    setMinimumSize(400, 720);
    resize(minimumSize());
    setStyleSheet("background-color: #01200F;");
}

void PrimaryWindow::resizeEvent(QResizeEvent *event)
{
    if(IsAppLayout && size().width() > AppLayoutMaxX)
    {
        SceneManager& _sceneManager = SceneManager::Get();
        IsAppLayout = false;
        _sceneManager.UpdateCurrentScene();
    }
    else if (!IsAppLayout && size().width() < AppLayoutMaxX)
    {
        SceneManager& _sceneManager = SceneManager::Get();
        IsAppLayout = true;
        _sceneManager.UpdateCurrentScene();
    }

    qDebug() << IsAppLayout;
}
