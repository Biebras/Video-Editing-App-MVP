#ifndef VIDEOGALLERYSCENE_H
#define VIDEOGALLERYSCENE_H

#include "scene.h"
#include <QtWidgets>
#include <QVideoWidget>
#include "videomanager.h"
#include "projectmanager.h"
#include "scenemanager.h"

class VideoGalleryScene : public Scene
{
    Q_OBJECT
    public:
        VideoGalleryScene(QString sceneName) : Scene(sceneName)
        {
            CreateWidgets();
            ArrangeWidgets();
            MakeConnections();
        };

        void UpdateScene() override;

    private:
        void CreateWidgets() override;
        void ArrangeWidgets() override;
        void MakeConnections() override;
        void CreateWidgetsForVideoGallery();

        VideoManager& _videoManager = VideoManager::Get();
        ProjectManager& _projectManager = ProjectManager::Get();
        SceneManager& _sceneManager = SceneManager::Get();
        QVBoxLayout* _videoLayout = new QVBoxLayout();
        QPushButton* _backButton;
        QLabel* _title;
        QPushButton* _addVideos;
        QList<QPushButton*> _selectVideos;
        QVBoxLayout* _mainLayout;

    public slots:
        void GoBack();
};

#endif // VIDEOGALLERYSCENE_H
