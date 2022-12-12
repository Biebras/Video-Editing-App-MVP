#ifndef TRIMSCENE_H
#define TRIMSCENE_H

#include "scene.h"
#include <QtWidgets>
#include <QVideoWidget>

class TrimScene : public Scene
{
    public:
        TrimScene() : Scene()
        {
            CreateWidgets();
            ArrangeWidgets();
            MakeConnections();
        };

    private:
        void CreateWidgets();
        void ArrangeWidgets();
        void MakeConnections();
        QPushButton* _backButton;
        QPushButton* _shareButton;
        QPushButton* _addButton;
        QVideoWidget* _videoWidget;
        QLabel* _timeLabel;
        QPushButton* _pauseButton;
        QSlider* _videoSlider;
        QSlider* _videoSlider2;
        QPushButton* _volumeButton;
        QPushButton* _trimButton;
        QPushButton* _effectButton;
        QPushButton* _audioButton;
};

#endif // TRIMSCENE_H
