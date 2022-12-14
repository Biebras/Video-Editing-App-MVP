#include "editscene.h"
#include "modularlayout.h"
#include "scenemanager.h"
#include "videomanager.h"
#include <iostream>
#include <QDebug>

void EditScene::CreateWidgets()
{
    // header
    _backButton = new QPushButton("");
    _backButton->setIcon(QIcon(":/icons/backIcon.png"));
    _backButton->setToolTip("Go Back");
    _backButton->setFixedSize(QSize(50, 50));
    _shareButton = new QPushButton();
    _shareButton->setIcon(QIcon(":/icons/shareIcon.png"));
    _shareButton->setToolTip("Share");
    _shareButton->setFixedSize(QSize(50, 50));
    _addButton = new QPushButton();
    _addButton->setIcon(QIcon(":/icons/addIcon.png"));
    _addButton->setToolTip("Add Video");
    _addButton->setFixedSize(QSize(50,50));

    // video area
    _videoWidget = new QVideoWidget();
    _videoPlayer = new VideoPlayer();
    _videoPlayer->setVideoOutput(_videoWidget);

    //  if there is at least one video in the project, play it
    if (_videoManager->GetTotalVideos() > 0)
    {
        _videoPlayer->setMedia(QUrl(QUrl::fromLocalFile(_videoManager->GetVideo(0)->GetFilePath())));
        _videoPlayer->SetCurrentVideo(_videoManager->GetVideo(0));
        _videoPlayer->play();
    }

    // initialise the duration index and total duration
    _durationIndex = 0;
    _totalDuration = 0;

    // time area
    _timeLabel = new QLabel();
    _timeLabel->setAlignment(Qt::AlignCenter);
    _timeLabel->setStyleSheet("font-size: 14pt");

    // pause/play area
    _pauseButton = new QPushButton();
    _pauseButton->setIcon(QIcon(":/icons/pauseIcon.png"));
    _pauseButton->setToolTip("Pause");
    _pauseButton->setFixedSize(QSize(50, 50));
    _pauseButton->setEnabled(false);
    _volumeButton = new QPushButton();
    _volumeButton->setIcon(QIcon(":/icons/muteIcon.png"));
    _volumeButton->setToolTip("Mute Volume");
    _volumeButton->setFixedSize(QSize(50, 50));

    // slider area
    _videoSlider = new QSlider();
    _videoSlider->setOrientation(Qt::Horizontal);
    _videoSlider->setToolTip("Move through video");
    _videoSlider->setTickInterval(1000);
    _videoSlider->setEnabled(false);

    // thumbnails
    // loop through videos
    for (int i = 0; i < _videoManager->GetTotalVideos(); i++)
    {
        _thumbnails.append(new QPushButton());
        _thumbnails[i]->setFixedHeight(80);
        _thumbnails[i]->setToolTip("Reorder Video");
        QString filePath = _videoManager->GetVideo(i)->GetFilePath();
        QString thumbnailPath = filePath.left(filePath.length() - 4) + ".png";
        if (QFile(thumbnailPath).exists()) // if file exists
        {
            QImageReader *imageReader = new QImageReader(thumbnailPath);
            QImage sprite = imageReader->read(); // read the thumbnail image
            if (!sprite.isNull())
            {
                _thumbnails[i]->setIcon(QIcon(QPixmap::fromImage(sprite)));
                //_thumbnails[i]->setIconSize(_thumbnails[i]->size());
                _thumbnails[i]->setIconSize(QSize(_thumbnails[i]->width() - 20, _thumbnails[i]->height() - 20));
            } else
                _thumbnails[i]->setText("No thumbnail for this video");
        } else
            _thumbnails[i]->setText("No thumbnail for this video");
        _thumbnails[i]->setEnabled(false);
    }

    // reorder buttons
    _moveLeft = new QPushButton();
    _moveLeft->setIcon(QIcon(":/icons/backIcon.png"));
    _moveLeft->setFixedSize(QSize(50, 50));
    _moveLeft->setEnabled(false);
    _moveRight = new QPushButton();
    _moveRight->setIcon(QIcon(":/icons/rightIcon.png"));
    _moveRight->setFixedSize(QSize(50, 50));
    _moveRight->setEnabled(false);

    // footer
    _trimButton = new QPushButton();
    _trimButton->setIcon(QIcon(":/icons/trimIcon.png"));
    _trimButton->setToolTip("Trim Video");
    _trimButton->setFixedSize(QSize(50, 50));
    _effectButton = new QPushButton();
    _effectButton->setIcon(QIcon(":/icons/effectIcon.png"));
    _effectButton->setToolTip("Add Effects");
    _effectButton->setFixedSize(QSize(50, 50));
    _audioButton = new QPushButton();
    _audioButton->setIcon(QIcon(":/icons/muteIcon.png"));
    _audioButton->setToolTip("Add Audio");
    _audioButton->setFixedSize(QSize(50, 50));
}

void EditScene::ArrangeWidgets()
{
    // create the layouts for each area
    ModularLayout* header = new ModularLayout();
    header->addWidget(_backButton);
    header->addStretch();
    header->addWidget(_shareButton);
    header->addWidget(_addButton);

//    ModularLayout* videoArea = new ModularLayout();
    _videoArea->addWidget(_videoWidget);

    ModularLayout* timeArea = new ModularLayout();
    timeArea->addWidget(_timeLabel);

    ModularLayout* pauseArea = new ModularLayout();
    pauseArea->addStretch();
    pauseArea->addWidget(_pauseButton);
    pauseArea->addWidget(_volumeButton);
    pauseArea->addStretch();

    ModularLayout* videoEditArea = new ModularLayout();
    videoEditArea->addWidget(_videoSlider);

//    ModularLayout* thumbnailArea = new ModularLayout();
    for (auto thumbnail : _thumbnails)
    {
        _thumbnailArea->addWidget(thumbnail);
    }
    _thumbnailArea->setSpacing(0);

    ModularLayout* reorderArea = new ModularLayout();
    reorderArea->addStretch();
    reorderArea->addWidget(_moveLeft);
    reorderArea->addWidget(_moveRight);
    reorderArea->addStretch();

    ModularLayout* footer = new ModularLayout();
    footer->addStretch();
    footer->addWidget(_trimButton);
    footer->addWidget(_effectButton);
    footer->addWidget(_audioButton);
    footer->addStretch();

    // set the layout of all the layout widgets
    header->GetLayoutWidget()->setLayout(header);
    _videoArea->GetLayoutWidget()->setLayout(_videoArea);
    timeArea->GetLayoutWidget()->setLayout(timeArea);
    pauseArea->GetLayoutWidget()->setLayout(pauseArea);
    videoEditArea->GetLayoutWidget()->setLayout(videoEditArea);
    _thumbnailArea->GetLayoutWidget()->setLayout(_thumbnailArea);
    reorderArea->GetLayoutWidget()->setLayout(reorderArea);
    footer->GetLayoutWidget()->setLayout(footer);

    // set each layout widget to show in the main layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(header->GetLayoutWidget());
    mainLayout->addWidget(_videoArea->GetLayoutWidget(), 4);
    mainLayout->addWidget(timeArea->GetLayoutWidget());
    mainLayout->addWidget(pauseArea->GetLayoutWidget());
    mainLayout->addWidget(videoEditArea->GetLayoutWidget());
    mainLayout->addWidget(_thumbnailArea->GetLayoutWidget());
    mainLayout->addWidget(reorderArea->GetLayoutWidget());
    mainLayout->addWidget(footer->GetLayoutWidget());

    this->setLayout(mainLayout);
}

void EditScene::UpdateScene()
{
   // update thumbnails
    while (_thumbnailArea->count() > 0)
    {
        QWidget *w = _thumbnailArea->takeAt(0)->widget();
        if (w)
            w->deleteLater();
    }
    _thumbnails.clear();

    for (int i = 0; i < _videoManager->GetTotalVideos(); i++)
    {
        _thumbnails.append(new QPushButton());
        _thumbnails[i]->setFixedHeight(80);
        _thumbnails[i]->setToolTip("Reorder Video");
        QString filePath = _videoManager->GetVideo(i)->GetFilePath();
        QString thumbnailPath = filePath.left(filePath.length() - 4) + ".png";
        if (QFile(thumbnailPath).exists()) // if file exists
        {
            QImageReader *imageReader = new QImageReader(thumbnailPath);
            QImage sprite = imageReader->read(); // read the thumbnail image
            if (!sprite.isNull())
            {
                _thumbnails[i]->setIcon(QIcon(QPixmap::fromImage(sprite)));
                _thumbnails[i]->setIconSize(QSize(_thumbnails[i]->width() - 20, _thumbnails[i]->height() - 20));
            } else
                _thumbnails[i]->setText("No thumbnail for this video");
        } else
            _thumbnails[i]->setText("No thumbnail for this video");
        _thumbnails[i]->setEnabled(false);
        _thumbnailArea->addWidget(_thumbnails[i]);
    }

    // reset duration index and total duration
    _durationIndex = 0;
    _totalDuration = 0;

    // remove from video area
    while (_videoArea->count() > 0)
    {
        QWidget *w = _videoArea->takeAt(0)->widget();
        if (w)
            w->deleteLater();
    }

    // video area
    _videoWidget = new QVideoWidget();
    _videoPlayer = new VideoPlayer();
    _videoPlayer->setVideoOutput(_videoWidget);

    _videoArea->addWidget(_videoWidget);

    // reconnect signals and slots

    //  if there is at least one video in the project, play it
    if (_videoManager->GetTotalVideos() > 0)
    {
        _videoPlayer->setMedia(QUrl(QUrl::fromLocalFile(_videoManager->GetVideo(0)->GetFilePath())));
        _videoPlayer->SetCurrentVideo(_videoManager->GetVideo(0));
        _videoPlayer->play();
    }

    // when thumbnail buttons pressed, allow user to reorder the video they have chosen
    for (auto thumbnail : _thumbnails)
        connect(thumbnail, SIGNAL(clicked()), this, SLOT(thumbnailClicked()));

    // when the position of the video changes, set the current time, the time label, the video slider and initially load videos to set their details
    connect(_videoPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(changeTime(qint64)));

    // when a video ends, play the next video in the project
    connect(_videoPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(changeMediaStatus(QMediaPlayer::MediaStatus)));



}

void EditScene::MakeConnections()
{
    /** connections:
     *  back button -> projects scene
     *  share button -> export scene
     *  add button -> video library scene
     *  trim button -> trim scene
     *  effect button -> fx scene
     *  audio button -> audio scene
    **/

    // when back button pressed go to projects scene
    connect(_backButton, SIGNAL(clicked()), this, SLOT(showProjects()));

    // when add button pressed, go to video library scene
    connect(_addButton, SIGNAL(clicked()), this, SLOT(showVideoLibrary()));

    // when thumbnail buttons pressed, allow user to reorder the video they have chosen
    for (auto thumbnail : _thumbnails)
        connect(thumbnail, SIGNAL(clicked()), this, SLOT(thumbnailClicked()));

    // when reorder buttons pressed, change the order of the videos in video manager
    connect(_moveLeft, SIGNAL(clicked()), this, SLOT(reorderLeft()));
    connect(_moveRight, SIGNAL(clicked()), this, SLOT(reorderRight()));

    // when pause button pressed, either pause or play video
    connect(_pauseButton, SIGNAL(clicked()), this, SLOT(pausePlay()));

    // when the position of the video changes, set the current time, the time label, the video slider and initially load videos to set their details
    connect(_videoPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(changeTime(qint64)));

    // when the slider is moved, update the current time and check if the video needs updating
    connect(_videoSlider, SIGNAL(sliderMoved(int)), this, SLOT(movedSlider(int)));

    // when the user starts moving the slider, pause the video
    connect(_videoSlider, SIGNAL(sliderPressed()), this, SLOT(pressedSlider()));

    // when the user releases the slider, play the video
    connect(_videoSlider, SIGNAL(sliderReleased()), this, SLOT(releasedSlider()));

    // when a video ends, play the next video in the project
    connect(_videoPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(changeMediaStatus(QMediaPlayer::MediaStatus)));

    // when volume button pressed, mute or unmute video
    connect(_volumeButton, SIGNAL(clicked()), this, SLOT(changeVolume()));
}

void EditScene::thumbnailClicked()
{
    // enable move left and right buttons
    _moveLeft->setEnabled(true);
    _moveRight->setEnabled(true);

    // get the index of the button that was pressed
    _reorderVideoIndex = _thumbnails.indexOf(qobject_cast<QPushButton* >(QObject::sender()));

    // disable thumbnail buttons except the one we are moving
    for (int i =0; i < _thumbnails.size(); i++)
    {
        if (i != _reorderVideoIndex)
            _thumbnails[i]->setEnabled(false);
    }

    if (_reorderVideoIndex == 0)
        _moveLeft->setEnabled(false);
    else if (_reorderVideoIndex == _thumbnails.size()-1)
        _moveRight->setEnabled(false);
}

void EditScene::reorderLeft()
{
    for (auto thumbnail : _thumbnails)
        thumbnail->setEnabled(true);
    _moveLeft->setEnabled(false);
    _moveRight->setEnabled(false);

    // swap videos
    Video* second = _videoManager->GetVideo(_reorderVideoIndex);
    int secondEnd = second->GetEnd();
    int secondDuration = second->GetDuration();
    int firstStart = _videoManager->GetVideo(_reorderVideoIndex-1)->GetStart();
    _videoManager->RemoveVideo(_videoManager->GetVideo(_reorderVideoIndex));
    _videoManager->InsertVideo(_reorderVideoIndex-1, second);

    // recalculate start and end times of videos
    // first video should have start of initial first video
    _videoManager->GetVideo(_reorderVideoIndex-1)->SetStart(firstStart);
    // first video should have end of its start + its duration
    _videoManager->GetVideo(_reorderVideoIndex-1)->SetEnd(firstStart+secondDuration);
    // second video start should have first videos end
    _videoManager->GetVideo(_reorderVideoIndex)->SetStart(_videoManager->GetVideo(_reorderVideoIndex-1)->GetEnd());
    // second video end should be the same end as the initial second video
    _videoManager->GetVideo(_reorderVideoIndex)->SetEnd(secondEnd);

    // swap icons
    QIcon tempIcon = _thumbnails[_reorderVideoIndex]->icon();
    _thumbnails[_reorderVideoIndex]->setIcon(_thumbnails[_reorderVideoIndex-1]->icon());
    _thumbnails[_reorderVideoIndex-1]->setIcon(tempIcon);

    // check if current video playing needs updating and play it
    int time = _videoPlayer->GetCurrentTime2();
    _videoPlayer->Update();
    _videoPlayer->Play(time);
    _pauseButton->setIcon(QIcon(":/icons/pauseIcon.png"));
}

void EditScene::reorderRight()
{
    for (auto thumbnail : _thumbnails)
        thumbnail->setEnabled(true);
    _moveLeft->setEnabled(false);
    _moveRight->setEnabled(false);

    // swap videos
    Video* first = _videoManager->GetVideo(_reorderVideoIndex);
    int firstStart = first->GetStart();
    int secondEnd = _videoManager->GetVideo(_reorderVideoIndex+1)->GetEnd();
    int secondDuration = _videoManager->GetVideo(_reorderVideoIndex+1)->GetDuration();
    _videoManager->RemoveVideo(_videoManager->GetVideo(_reorderVideoIndex));
    _videoManager->InsertVideo(_reorderVideoIndex+1, first);

    // first videos start should be the initial first videos start
    _videoManager->GetVideo(_reorderVideoIndex)->SetStart(firstStart);
    // first videos end should be its start + its duration
    _videoManager->GetVideo(_reorderVideoIndex)->SetEnd(firstStart + secondDuration);
    // second videos start should be first videos end
    _videoManager->GetVideo(_reorderVideoIndex+1)->SetStart(_videoManager->GetVideo(_reorderVideoIndex)->GetEnd());
    // second videos end should be initial second videos end
    _videoManager->GetVideo(_reorderVideoIndex+1)->SetEnd(secondEnd);

    // swap icons
    QIcon tempIcon = _thumbnails[_reorderVideoIndex]->icon();
    _thumbnails[_reorderVideoIndex]->setIcon(_thumbnails[_reorderVideoIndex+1]->icon());
    _thumbnails[_reorderVideoIndex+1]->setIcon(tempIcon);

    // check if current video playing needs updating and play it
    int time = _videoPlayer->GetCurrentTime2();
    _videoPlayer->Update();
    _videoPlayer->Play(time);
    _pauseButton->setIcon(QIcon(":/icons/pauseIcon.png"));
}

void EditScene::pausePlay()
{
    // change icon and state based on current state
    if (_videoPlayer->state() == QMediaPlayer::PausedState)
    {
        _videoPlayer->play();
        _pauseButton->setIcon(QIcon(":/icons/pauseIcon.png"));
        _pauseButton->setToolTip("Pause");
    } else
    {
        _videoPlayer->Pause();
        _pauseButton->setIcon(QIcon(":/icons/playIcon.png"));
        _pauseButton->setToolTip("Play");
    }
}

void EditScene::changeTime(qint64 time)
{
    // update current time of video player
    Video* currentVid = _videoPlayer->GetCurrentVideo();
    int actualTime = time + currentVid->GetStart();
    _videoPlayer->SetCurrentTime(actualTime);

    //split the time into corresponding mins, secs and millisecs
    int seconds = actualTime/1000 % 60;
    int minutes = actualTime/60000;
    int mseconds = actualTime % 60;

    // get total duration of videos
    int total = _videoManager->GetTotalDuration();

    int totalSeconds = total/1000 % 60;
    int totalMinutes = total/60000;
    int totalMseconds = total % 60;

    // format the time into a string to display
    char timeStr[22];
    std::sprintf(timeStr, "%02d:%02d:%02d/%02d:%02d:%02d", minutes, seconds, mseconds, totalMinutes, totalSeconds, totalMseconds);
    _timeLabel->setText(QString::fromStdString(timeStr));

    // adjust the slider to the current time
    _videoSlider->setValue(actualTime);
    _videoSlider->setMaximum(total);


    // find the durations of the videos by playing each one at the start
    if (_videoPlayer->duration() > 0 && _durationIndex < _videoManager->GetTotalVideos() - 1)
    {
        // set the start and end of current video and change the video playing to the next one
        _videoManager->GetVideo(_durationIndex)->SetStart(_totalDuration);
        _totalDuration += _videoPlayer->duration();
        _videoManager->GetVideo(_durationIndex)->SetEnd(_totalDuration);
        _durationIndex++;
        _videoPlayer->setMedia(QUrl(QUrl::fromLocalFile(_videoManager->GetVideo(_durationIndex)->GetFilePath())));
        _videoPlayer->SetCurrentVideo(_videoManager->GetVideo(_durationIndex));
        _videoPlayer->play();
    }
    else if (_videoPlayer->duration() > 0 && _durationIndex == _videoManager->GetTotalVideos() - 1)
    {
        // all videos loaded
        // set the start and end of current video and change the video playing to the first one
        _videoManager->GetVideo(_durationIndex)->SetStart(_totalDuration);
        _totalDuration += _videoPlayer->duration();
        _videoManager->GetVideo(_durationIndex)->SetEnd(_totalDuration);
        _videoPlayer->setMedia(QUrl(QUrl::fromLocalFile(_videoManager->GetVideo(0)->GetFilePath())));
        _videoPlayer->SetCurrentVideo(_videoManager->GetVideo(0));
        _videoPlayer->SetCurrentTime(0);
        _videoPlayer->Play(_videoPlayer->GetCurrentTime2());
        _durationIndex++;
        _pauseButton->setEnabled(true);
        _videoSlider->setEnabled(true);
        _volumeButton->setEnabled(true);
        for (auto thumbnail : _thumbnails)
            thumbnail->setEnabled(true);
    }
}

void EditScene::movedSlider(int val)
{
    // update the current time to the value on the slider
    _videoPlayer->SetCurrentTime(val);
    // check if the video playing should be updated
    _videoPlayer->Update();
}

void EditScene::pressedSlider()
{
    // pause the video and set icon
    _videoPlayer->pause();
    _pauseButton->setIcon(QIcon(":icons/playIcon.png"));
}

void EditScene::releasedSlider()
{
    // play the video and set icon
    _videoPlayer->Play(_videoPlayer->GetCurrentTime2());
    _pauseButton->setIcon(QIcon(":icons/pauseIcon.png"));

}

void EditScene::changeMediaStatus(QMediaPlayer::MediaStatus status)
{
    // if at end of video, update the video currently playing
    if (status == QMediaPlayer::EndOfMedia)
    {
        _videoPlayer->SetCurrentTime(_videoPlayer->GetCurrentVideo()->GetEnd());
        _videoPlayer->Update();
        _videoPlayer->Play(_videoPlayer->GetCurrentTime2());
    }
}

void EditScene::changeVolume()
{
    // if muted, unmute
    if (_videoPlayer->GetCurrentVideo()->GetVolume() > 0)
    {
        _videoPlayer->GetCurrentVideo()->SetVolume(0);
        _volumeButton->setIcon(QIcon(":icons/muteIcon.png"));
        _volumeButton->setToolTip("Unmute video");
        _videoPlayer->setVolume(0);
    } else
    {
        // if unmuted, mute
        _videoPlayer->GetCurrentVideo()->SetVolume(1);
        _volumeButton->setIcon(QIcon(":icons/volumeIcon.png"));
        _volumeButton->setToolTip("Mute video");
        _videoPlayer->setVolume(100);
    }
}

void EditScene::showProjects()
{
    _videoPlayer->setMedia(QMediaContent());
    _timeLabel->setText("00:00:00/00:00:00");
    _pauseButton->setEnabled(false);
    _volumeButton->setEnabled(false);
    _videoSlider->setSliderPosition(0);
    _videoSlider->setEnabled(false);
    _sceneManager.SetScene("projects");
}

void EditScene::showVideoLibrary()
{
    _sceneManager.SetScene("gallery");
}
