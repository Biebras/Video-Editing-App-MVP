#ifndef VIDEOGALLERYSCENE_H
#define VIDEOGALLERYSCENE_H

#include "scene.h"
#include <QtWidgets>
#include <QVideoWidget>

class VideoGalleryScene : public Scene
{
    public:
        VideoGalleryScene(QString sceneName) : Scene(sceneName)
        {
            CreateWidgets();
            ArrangeWidgets();
            MakeConnections();
        };

    private:
        void CreateWidgets() override;
        void ArrangeWidgets() override;
        void MakeConnections() override;

        QPushButton* _backButton;
        QLabel* _title;
        QPushButton* _addVideos;
        QList<QPushButton*> _selectVideos;
        QVBoxLayout* _mainLayout;
};

#endif // VIDEOGALLERYSCENE_H
