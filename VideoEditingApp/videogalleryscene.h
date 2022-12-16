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
            // initialise the scene
            CreateWidgets();
            ArrangeWidgets();
            MakeConnections();
        };

        void UpdateScene() override;
        void Retranslate() override;

    private:
        void CreateWidgets() override;
        void ArrangeWidgets() override;
        void MakeConnections() override;
        void CreateWidgetsForVideoGallery();

        VideoManager& _videoManager = VideoManager::Get();
        ProjectManager& _projectManager = ProjectManager::Get();
        SceneManager& _sceneManager = SceneManager::Get();
        QGridLayout* _videoLayout = new QGridLayout();
        QPushButton* _backButton;
        QLabel* _title;
        QPushButton* _addVideos;
        QList<QPushButton*> _selectVideos;
        QVBoxLayout* _mainLayout;

    public slots:
        void GoBack();
        void AddVideo();
        void FindVideos();
};

#endif // VIDEOGALLERYSCENE_H
