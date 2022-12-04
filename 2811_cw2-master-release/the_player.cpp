//
// Created by twak on 11/11/2019.
//

#include "the_player.h"
#include <iostream>


// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i)
{
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

// change the image and video for one button every one second
void ThePlayer::shuffle()
{
    TheButtonInfo* i = & infos -> at (rand() % infos->size() );
//        setMedia(*i->url);
    buttons -> at( updateCount++ % buttons->size() ) -> init( i );
}

void ThePlayer::playStateChanged (QMediaPlayer::State ms)
{ 
    switch (ms)
    {
        case QMediaPlayer::State::StoppedState:
            play(); // starting playing again...
            break;
    default:
        break;
    }

}

void ThePlayer::jumpTo (TheButtonInfo* button)
{
    setMedia( * button -> url);
    play();
}

void ThePlayer::timeChanged(qint64 time)
{
    //split the time into corresponding mins, secs and millisecs
    int seconds = time/1000 % 60;
    int minutes = time/60000;
    int mseconds = time % 60;
    // format the time in a string making sure there are leading 0s
    char timeStr[10];
    std::sprintf(timeStr, "%02d:%02d:%02d", minutes, seconds, mseconds);
    timeLabel->setText(QString::fromStdString(timeStr));

    // adjust the slider to the current time
    videoSlider.setValue(time);
    videoSlider.setMaximum(this->duration());
}

void ThePlayer::pauseButtonPressed()
{
    if (this->state() == QMediaPlayer::PausedState) {
        this->play();
        pauseButton.setIcon(QIcon(":/pauseIcon.png"));
    } else {
        this->pause();
        pauseButton.setIcon(QIcon(":/playIcon.png"));
    }
}

void ThePlayer::movedSlider(int val)
{
    // changes the place in the video we are at
    this->setPosition(val);
}

void ThePlayer::pressedSlider()
{
    this->pause();
    pauseButton.setIcon(QIcon(":/playIcon.png"));
}

void ThePlayer::releasedSlider()
{
    this->play();
    pauseButton.setIcon(QIcon(":/pauseIcon.png"));
}
