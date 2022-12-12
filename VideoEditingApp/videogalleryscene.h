#ifndef VIDEOGALLERYSCENE_H
#define VIDEOGALLERYSCENE_H

#include "scene.h"
#include <QtWidgets>
#include <QVideoWidget>

class VideoGalleryScene : public Scene
{
    public:
        VideoGalleryScene() : Scene()
        {
            CreateWidgets();
            ArrangeWidgets();
            MakeConnections();
        }

    private:
        void CreateWidgets();
        void ArrangeWidgets();
        void MakeConnections();
        QPushButton* _backButton;
        QLabel* _title;
        QPushButton* _addVideos;
        QList<QPushButton*> _selectVideos;
};

#endif // VIDEOGALLERYSCENE_H
