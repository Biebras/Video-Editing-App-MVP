#ifndef TRIMSCENE_H
#define TRIMSCENE_H

#include "scene.h"
#include <QtWidgets>
#include <QVideoWidget>

class TrimScene : public Scene
{
    public:
        TrimScene(QString sceneName) : Scene(sceneName)
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
