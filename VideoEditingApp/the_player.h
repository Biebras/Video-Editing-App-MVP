//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>
#include <QLabel>
#include <QSlider>

class ThePlayer : public QMediaPlayer
{
    Q_OBJECT

    private:
        std::vector<TheButtonInfo>* infos;
        std::vector<TheButton*>* buttons;
        QTimer* mTimer;
        long updateCount = 0;

    public:
        ThePlayer() : QMediaPlayer(NULL)
        {
            setVolume(0); // be slightly less annoying
            videoSlider.setMaximum(this->duration()); // set the max to length of video
            connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );

            mTimer = new QTimer(NULL);
            mTimer->setInterval(1000); // 1000ms is one second between ...
            mTimer->start();
            connect( mTimer, SIGNAL (timeout()), SLOT ( shuffle() ) ); // ...running shuffle method

            // when the time stamp of the video changes, update the timer label and slider
            connect(this, SIGNAL(positionChanged(qint64)), this, SLOT(timeChanged(qint64)));

            // when the pause button is pressed, pause or play the video
            connect(&pauseButton, SIGNAL(clicked()), this, SLOT(pauseButtonPressed()));



            // when user moves slider, change time of video
            connect(&videoSlider, SIGNAL(sliderMoved(int)), this, SLOT(movedSlider(int)));

            // when the user starts moving the slider, pause the video
            connect(&videoSlider, SIGNAL(sliderPressed()), this, SLOT(pressedSlider()));

            // when the user releases the slider, play the video
            connect(&videoSlider, SIGNAL(sliderReleased()), this, SLOT(releasedSlider()));

        }

        // all buttons have been setup, store pointers here
        void setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i);

        // label to show the time stamp of the video
        QLabel* timeLabel;

        QPushButton pauseButton;

        QSlider videoSlider;

    private slots:

        // change the image and video for one button every one second
        void shuffle();

        void playStateChanged (QMediaPlayer::State ms);

        void timeChanged(qint64 time);

        void pauseButtonPressed();

        void movedSlider(int val);

        void pressedSlider();

        void releasedSlider();

    public slots:

        // start playing this ButtonInfo
        void jumpTo (TheButtonInfo* button);

};

#endif //CW2_THE_PLAYER_H
