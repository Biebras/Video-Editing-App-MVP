#ifndef EDITSCENE_H
#define EDITSCENE_H

#include "scene.h"
#include "videoplayer.h"
#include <QtWidgets>
#include <QVideoWidget>

class EditScene : public Scene
{
    Q_OBJECT
    public:
        EditScene() : Scene()
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
        VideoPlayer* _videoPlayer;
        QLabel* _timeLabel;
        QPushButton* _pauseButton;
        QSlider* _videoSlider;
        QPushButton* _volumeButton;
        QPushButton* _trimButton;
        QPushButton* _effectButton;
        QPushButton* _audioButton;
        QList<QPushButton*> _thumbnails;
        QPushButton* _moveLeft;
        QPushButton* _moveRight;
        int _reorderVideoIndex; // the index of the video to be reordered

    public slots:
        void thumbnailClicked();
        void reorderLeft();
        void reorderRight();
        void pausePlay();
};

#endif // EDITSCENE_H
