#ifndef EDITSCENE_H
#define EDITSCENE_H

#include "scene.h"
#include <QtWidgets>
#include <QVideoWidget>

class EditScene : public Scene
{
    public:
        EditScene() : Scene() {};
//        void CreateWidgets();
//        void ArrangeWidgets();
//        void MakeConnections();

    private:
        void CreateWidgets();
        void ArrangeWidgets();
        void MakeConnections();
        QPushButton* _backButton;
//        QPushButton* _shareButton;
//        QPushButton* _addButton;
//        QVideoWidget* _videoWidget;
//        QLabel* _timeLabel;
//        QPushButton* _pauseButton;
//        QSlider* _videoSlider;
//        QPushButton* _volumeButton;
//        QPushButton* _trimButton;
//        QPushButton* _effectButton;
//        QPushButton* _audioButton;

};

#endif // EDITSCENE_H
