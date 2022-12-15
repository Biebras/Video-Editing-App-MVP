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
    _backButton->setIcon(QIcon(":/icons/backButton.svg"));
    _backButton->setToolTip(tr("Go Back"));
    _backButton->setFixedSize(QSize(30, 30));
    _backButton->setIconSize(QSize(25, 25));
    _backButton->setStyleSheet("QPushButton {border-radius: 5px; background-color: #011502; } QPushButton:hover { background-color: #044220; }");

    _saveButton = new QPushButton();
    _saveButton->setIcon(QIcon(":/icons/save.svg"));
    _saveButton->setToolTip(tr("Save"));
    _saveButton->setFixedSize(QSize(30, 30));
    _saveButton->setIconSize(QSize(25, 25));
    _saveButton->setStyleSheet("QPushButton {border-radius: 5px; background-color: #011502; } QPushButton:hover { background-color: #044220; }");

    _addButton = new QPushButton();
    _addButton->setIcon(QIcon(":/icons/addIcon.svg"));
    _addButton->setToolTip(tr("Add Video"));
    _addButton->setFixedSize(QSize(30,30));
    _addButton->setIconSize(QSize(25, 25));
    _addButton->setStyleSheet("QPushButton {border-radius: 5px; background-color: #011502; } QPushButton:hover { background-color: #044220; }");

    // video area
    _videoWidget = new QVideoWidget();
    _videoPlayer = new VideoPlayer();
    _videoPlayer->setVideoOutput(_videoWidget);

    //  if there is at least one video in the project, play it
    if (_videoManager.GetTotalVideos() > 0)
    {
        _videoPlayer->setMedia(QUrl(QUrl::fromLocalFile(_videoManager.GetVideo(0)->GetFilePath())));
        _videoPlayer->SetCurrentVideo(_videoManager.GetVideo(0));
        _videoPlayer->play();
    }

    // initialise the duration index and total duration
    _durationIndex = 0;
    _totalDuration = 0;

    // time area
    _timeLabel = new QLabel();
    _timeLabel->setAlignment(Qt::AlignCenter);
    _timeLabel->setStyleSheet("font-size: 11pt; color: #9EC5AB;");

    // pause/play area
    _pauseButton = new QPushButton();
    _pauseButton->setIcon(QIcon(":/icons/pauseIcon.svg"));
    _pauseButton->setToolTip(tr("Pause"));
    _pauseButton->setFixedSize(QSize(30, 30));
    _pauseButton->setIconSize(QSize(25, 25));
    _pauseButton->setStyleSheet("QPushButton {border-radius: 5px; background-color: #01200F; } QPushButton:hover { background-color: #044220; }");
    _pauseButton->setEnabled(false);

    _volumeButton = new QPushButton();
    _volumeButton->setIcon(QIcon(":/icons/muteIcon.svg"));
    _volumeButton->setToolTip(tr("Mute Volume"));
    _volumeButton->setFixedSize(QSize(30, 30));
     _volumeButton->setIconSize(QSize(25, 25));
    _volumeButton->setStyleSheet("QPushButton {border-radius: 5px; background-color: #01200F; } QPushButton:hover { background-color: #044220; }");

    // slider area
    _videoSlider = new QSlider();
    _videoSlider->setOrientation(Qt::Horizontal);
    _videoSlider->setToolTip(tr("Move through video"));

    _videoSlider->setStyleSheet("QSlider::groove:horizontal { border: 1px solid #104F55; height: 8px; background: #32746D; margin: 2px 0; border-radius: 5px;} QSlider::handle:horizontal { background: #9EC5AB; border: 1px solid #5c5c5c; width: 16px; height: 16px; border-radius: 8px; margin: -4px 0; }");
    _videoSlider->setTickInterval(100);
    _videoSlider->setEnabled(false);

    // thumbnails
    // loop through videos
    for (int i = 0; i < _videoManager.GetTotalVideos(); i++)
    {
        _thumbnails.append(new QPushButton());
        _thumbnails[i]->setStyleSheet("background-color: black;");
        _thumbnails[i]->setFixedHeight(80);
        _thumbnails[i]->setToolTip(tr("Reorder Video"));
        QString filePath = _videoManager.GetVideo(i)->GetFilePath();
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
                _thumbnails[i]->setText(tr("No thumbnail for this video"));
        } else
            _thumbnails[i]->setText(tr("No thumbnail for this video"));
        _thumbnails[i]->setEnabled(false);
    }


    // reorder buttons
    _moveLeft = new QPushButton();
    _moveLeft->setIcon(QIcon(":/icons/moveLeft.svg"));
    _moveLeft->setToolTip("Move left");
    _moveLeft->setFixedSize(QSize(30, 30));
    _moveLeft->setIconSize(QSize(25, 25));
    _moveLeft->setStyleSheet("QPushButton {border-radius: 5px; background-color: #01200F; } QPushButton:hover { background-color: #044220; }");
    _moveLeft->setEnabled(false);

    _moveRight = new QPushButton();
    _moveRight->setIcon(QIcon(":/icons/rightIcon.svg"));
    _moveRight->setToolTip("Move right");
    _moveRight->setFixedSize(QSize(30, 30));
    _moveRight->setIconSize(QSize(25, 25));
    _moveRight->setStyleSheet("QPushButton {border-radius: 5px; background-color: #01200F; } QPushButton:hover { background-color: #044220; }");
    _moveRight->setEnabled(false);

    _removeButton = new QPushButton();
    _removeButton->setIcon(QIcon(":/icons/removeIcon.svg"));
    _removeButton->setToolTip("Remove video");
    _removeButton->setFixedSize(QSize(30, 30));
    _removeButton->setIconSize(QSize(25, 25));
    _removeButton->setStyleSheet("QPushButton {border-radius: 5px; background-color: #01200F; } QPushButton:hover { background-color: #044220; }");
    _removeButton->setEnabled(false);

    // footer
    _trimButton = new QPushButton();
    _trimButton->setIcon(QIcon(":/icons/trimIcon.svg"));
    _trimButton->setToolTip(tr("Trim Video"));
    _trimButton->setFixedSize(QSize(30, 30));
    _trimButton->setIconSize(QSize(25, 25));
    _trimButton->setStyleSheet("QPushButton {border-radius: 5px; background-color: #011502; } QPushButton:hover { background-color: #044220; }");

    _effectButton = new QPushButton();
    _effectButton->setIcon(QIcon(":/icons/effectIcon.svg"));
    _effectButton->setToolTip(tr("Add Effects"));
    _effectButton->setFixedSize(QSize(30, 30));
    _effectButton->setIconSize(QSize(25, 25));
    _effectButton->setStyleSheet("QPushButton {border-radius: 5px; background-color: #011502; } QPushButton:hover { background-color: #044220; }");

    _audioButton = new QPushButton();
    _audioButton->setIcon(QIcon(":/icons/audioIcon.svg"));
    _audioButton->setToolTip(tr("Add Audio"));
    _audioButton->setFixedSize(QSize(30, 30));
    _audioButton->setIconSize(QSize(25, 25));
    _audioButton->setStyleSheet("QPushButton {border-radius: 5px; background-color: #011502; } QPushButton:hover { background-color: #044220; }");
}

void EditScene::ArrangeWidgets()
{
    // create the layouts for each area
    ModularLayout* header = new ModularLayout();
    header->addWidget(_backButton);
    header->addStretch();
    header->addWidget(_saveButton);
    header->addWidget(_addButton);
    header->GetLayoutWidget()->setStyleSheet("QWidget {background: #011502;}");

//    ModularLayout* videoArea = new ModularLayout();
    _videoArea->addWidget(_videoWidget);
    _videoArea->setSpacing(0);
    _videoArea->setMargin(0);

    ModularLayout* timeArea = new ModularLayout();
    timeArea->addWidget(_timeLabel);
    timeArea->GetLayoutWidget()->setStyleSheet("QWidget {background: #011502;}");

    ModularLayout* pauseArea = new ModularLayout();
    pauseArea->addStretch();
    pauseArea->addWidget(_pauseButton);
    pauseArea->addWidget(_volumeButton);
    pauseArea->addStretch();

    ModularLayout* videoEditArea = new ModularLayout();
    videoEditArea->setContentsMargins(1, 0, 1, 3);
    videoEditArea->addWidget(_videoSlider);

//    ModularLayout* thumbnailArea = new ModularLayout();
    for (auto thumbnail : _thumbnails)
    {
        _thumbnailArea->addWidget(thumbnail);
    }
    _thumbnailArea->setSpacing(0);
    _thumbnailArea->setMargin(0);

    ModularLayout* reorderArea = new ModularLayout();
    reorderArea->addStretch();
    reorderArea->addWidget(_moveLeft);
    reorderArea->addWidget(_moveRight);
    reorderArea->addWidget(_removeButton);
    reorderArea->addStretch();

    ModularLayout* footer = new ModularLayout();
    footer->addStretch();
    footer->addWidget(_trimButton);
    footer->addWidget(_effectButton);
    footer->addWidget(_audioButton);
    footer->addStretch();
    footer->GetLayoutWidget()->setStyleSheet("QWidget {background: #011502;}");

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

    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->setContentsMargins(0,0,0,0);

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

    for (int i = 0; i < _videoManager.GetTotalVideos(); i++)
    {
        _thumbnails.append(new QPushButton());
        _thumbnails[i]->setFixedHeight(80);
        _thumbnails[i]->setToolTip(tr("Reorder Video"));
        QString filePath = _videoManager.GetVideo(i)->GetFilePath();
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
                _thumbnails[i]->setText(tr("No thumbnail for this video"));
        } else
            _thumbnails[i]->setText(tr("No thumbnail for this video"));
        _thumbnails[i]->setEnabled(false);
        _thumbnails[i]->setStyleSheet("QPushButton { background: black; }");
        _thumbnailArea->addWidget(_thumbnails[i]);
    }

    // reset duration index and total duration
    _durationIndex = 0;
    _totalDuration = 0;

    // remove from video area
    QWidget *w = _videoArea->takeAt(0)->widget();
    if (w)
        w->deleteLater();
    delete _videoPlayer;


    // video area
    _videoWidget = new QVideoWidget();
    _videoPlayer = new VideoPlayer();
    _videoPlayer->setVideoOutput(_videoWidget);

    _videoArea->addWidget(_videoWidget);

    //  if there is at least one video in the project, play it

    if (_videoManager.GetTotalVideos() > 0)
    {
        _videoPlayer->setMedia(QUrl(QUrl::fromLocalFile(_videoManager.GetVideo(0)->GetFilePath())));
        _videoPlayer->SetCurrentVideo(_videoManager.GetVideo(0));
        _videoPlayer->play();
    }

    // reset time label
    _timeLabel->setText("00:00:00/00:00:00");

    //  disable these until video loads
    _pauseButton->setEnabled(false);
    _volumeButton->setEnabled(false);
    _videoSlider->setEnabled(false);
    _moveLeft->setEnabled(false);
    _moveRight->setEnabled(false);
    _removeButton->setEnabled(false);

    // resest buttons
    _videoSlider->setValue(0);
    _pauseButton->setIcon(QIcon(":icons/pauseIcon.svg"));
    _volumeButton->setIcon(QIcon(":icons/muteIcon.svg"));

    _videoPlayer->setNotifyInterval(100);



     // reconnect signals and slots

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
    // when back button pressed go to projects scene
    connect(_backButton, SIGNAL(clicked()), this, SLOT(showProjects()));

    // when add button pressed, go to video library scene
    connect(_addButton, SIGNAL(clicked()), this, SLOT(showVideoLibrary()));

    //save changes button
    connect(_saveButton, SIGNAL(clicked()), this, SLOT(saveChanges()));

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

    // when a video ends, play the next video in the project
    connect(_videoPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(changeMediaStatus(QMediaPlayer::MediaStatus)));

    // when volume button pressed, mute or unmute video
    connect(_volumeButton, SIGNAL(clicked()), this, SLOT(changeVolume()));

    // when remove video button pressed, remove the video
    connect(_removeButton, SIGNAL(clicked()), this, SLOT(removeVideo()));
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
    if (_reorderVideoIndex == _thumbnails.size()-1)
        _moveRight->setEnabled(false);
    _removeButton->setEnabled(true);
}

void EditScene::reorderLeft()
{
    for (auto thumbnail : _thumbnails)
        thumbnail->setEnabled(true);
    _moveLeft->setEnabled(false);
    _moveRight->setEnabled(false);
    _removeButton->setEnabled(false);

    // swap videos
    Video* second = _videoManager.GetVideo(_reorderVideoIndex);
    int secondEnd = second->GetEnd();
    int secondDuration = second->GetDuration();
    int firstStart = _videoManager.GetVideo(_reorderVideoIndex-1)->GetStart();
    _videoManager.RemoveVideo(_videoManager.GetVideo(_reorderVideoIndex));
    _videoManager.InsertVideo(_reorderVideoIndex-1, second);

    // recalculate start and end times of videos
    // first video should have start of initial first video
    _videoManager.GetVideo(_reorderVideoIndex-1)->SetStart(firstStart);
    // first video should have end of its start + its duration
    _videoManager.GetVideo(_reorderVideoIndex-1)->SetEnd(firstStart+secondDuration);
    // second video start should have first videos end
    _videoManager.GetVideo(_reorderVideoIndex)->SetStart(_videoManager.GetVideo(_reorderVideoIndex-1)->GetEnd());
    // second video end should be the same end as the initial second video
    _videoManager.GetVideo(_reorderVideoIndex)->SetEnd(secondEnd);

    // swap icons
    QIcon tempIcon = _thumbnails[_reorderVideoIndex]->icon();
    _thumbnails[_reorderVideoIndex]->setIcon(_thumbnails[_reorderVideoIndex-1]->icon());
    _thumbnails[_reorderVideoIndex-1]->setIcon(tempIcon);

    // check if current video playing needs updating and play it
    int time = _videoPlayer->GetCurrentTime2();
    _videoPlayer->Update();
    _videoPlayer->Play(time);
    _pauseButton->setIcon(QIcon(":/icons/pauseIcon.svg"));
}

void EditScene::reorderRight()
{
    for (auto thumbnail : _thumbnails)
        thumbnail->setEnabled(true);
    _moveLeft->setEnabled(false);
    _moveRight->setEnabled(false);
    _removeButton->setEnabled(false);

    // swap videos
    Video* first = _videoManager.GetVideo(_reorderVideoIndex);
    int firstStart = first->GetStart();
    int secondEnd = _videoManager.GetVideo(_reorderVideoIndex+1)->GetEnd();
    int secondDuration = _videoManager.GetVideo(_reorderVideoIndex+1)->GetDuration();
    _videoManager.RemoveVideo(_videoManager.GetVideo(_reorderVideoIndex));
    _videoManager.InsertVideo(_reorderVideoIndex+1, first);

    // first videos start should be the initial first videos start
    _videoManager.GetVideo(_reorderVideoIndex)->SetStart(firstStart);
    // first videos end should be its start + its duration
    _videoManager.GetVideo(_reorderVideoIndex)->SetEnd(firstStart + secondDuration);
    // second videos start should be first videos end
    _videoManager.GetVideo(_reorderVideoIndex+1)->SetStart(_videoManager.GetVideo(_reorderVideoIndex)->GetEnd());
    // second videos end should be initial second videos end
    _videoManager.GetVideo(_reorderVideoIndex+1)->SetEnd(secondEnd);

    // swap icons
    QIcon tempIcon = _thumbnails[_reorderVideoIndex]->icon();
    _thumbnails[_reorderVideoIndex]->setIcon(_thumbnails[_reorderVideoIndex+1]->icon());
    _thumbnails[_reorderVideoIndex+1]->setIcon(tempIcon);

    // check if current video playing needs updating and play it
    int time = _videoPlayer->GetCurrentTime2();
    _videoPlayer->Update();
    _videoPlayer->Play(time);
    _pauseButton->setIcon(QIcon(":/icons/pauseIcon.svg"));
}

void EditScene::pausePlay()
{
    // change icon and state based on current state
    if (_videoPlayer->state() == QMediaPlayer::PausedState)
    {
        _videoPlayer->play();
        _pauseButton->setIcon(QIcon(":/icons/pauseIcon.svg"));
        _pauseButton->setToolTip("Pause");
    } else
    {
        _videoPlayer->Pause();
        _pauseButton->setIcon(QIcon(":/icons/playIcon.svg"));
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
    int total = _videoManager.GetTotalDuration();

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
    if (_videoPlayer->duration() > 0 && _durationIndex < _videoManager.GetTotalVideos() - 1 && (_fin || _first))
    {
        _fin = false;
        _first = false;
        // change the video playing
        _videoPlayer->SetCurrentVideo(_videoManager.GetVideo(_durationIndex));

        // set the start and end of current video and change the video playing to the next one
        _videoManager.GetVideo(_durationIndex)->SetStart(_totalDuration);
        _totalDuration += _videoPlayer->duration();
        _videoManager.GetVideo(_durationIndex)->SetEnd(_totalDuration);

        _durationIndex++;

        // change the video playing
        _videoPlayer->setMedia(QUrl(QUrl::fromLocalFile(_videoManager.GetVideo(_durationIndex)->GetFilePath())));

        _fin = true;

    }
    else if (_videoPlayer->duration() > 1 &&_durationIndex == _videoManager.GetTotalVideos() - 1 && (_fin || _videoManager.GetTotalVideos() < 2))
    {
        // all videos loaded
        // set the start and end of current video and change the video playing to the first one
        if (_videoManager.GetTotalVideos() > 1)
        {
            _videoManager.GetVideo(_durationIndex)->SetStart(_totalDuration);
        }
        else
            _videoManager.GetVideo(_durationIndex)->SetStart(0);

        _totalDuration += _videoPlayer->duration();

        _videoManager.GetVideo(_durationIndex)->SetEnd(_totalDuration);
        _durationIndex += 1;
        _videoPlayer->setMedia(QUrl(QUrl::fromLocalFile(_videoManager.GetVideo(0)->GetFilePath())));

        _pauseButton->setEnabled(true);
        _volumeButton->setEnabled(true);
        _videoSlider->setEnabled(true);
        for (auto thumbnail : _thumbnails)
            thumbnail->setEnabled(true);

        _videoPlayer->SetCurrentTime(0);
        _videoPlayer->SetCurrentVideo(_videoManager.GetVideo(0));
        _videoPlayer->Play(_videoPlayer->GetCurrentTime2());
    }

}

void EditScene::movedSlider(int val)
{
    // update the current time to the value on the slider
    _videoPlayer->SetCurrentTime(val);
    // check if the video playing should be updatedpauseIcon
    _videoPlayer->Update();
    _videoPlayer->Play(_videoPlayer->GetCurrentTime2());
    _pauseButton->setIcon(QIcon(":icons/pauseIcon.svg"));
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
        _volumeButton->setIcon(QIcon(":icons/muteIcon.svg"));
        _volumeButton->setToolTip(tr("Unmute video"));
        _videoPlayer->setVolume(0);
    } else
    {
        // if unmuted, mute
        _videoPlayer->GetCurrentVideo()->SetVolume(1);
        _volumeButton->setIcon(QIcon(":icons/volumeIcon.svg"));
        _volumeButton->setToolTip(tr("Mute video"));
        _videoPlayer->setVolume(100);
    }
}

void EditScene::removeVideo()
{
    // remove video at _reorderVideoIndex from the project

    // recalculate the start and end times of videos after this one
    int dur = 0;
    for (int i = _videoManager.GetTotalVideos()-1; i > _reorderVideoIndex; i--)
    {
        dur = _videoManager.GetVideo(i)->GetDuration();
        _videoManager.GetVideo(i)->SetStart(_videoManager.GetVideo(i-1)->GetStart());
        _videoManager.GetVideo(i)->SetEnd(_videoManager.GetVideo(i)->GetStart()+dur);
    }

    // remove video from video manager
    _videoManager.RemoveVideo(_videoManager.GetVideo(_reorderVideoIndex));
    _sceneManager.SetScene("edit");
}

void EditScene::showProjects()
{
    _sceneManager.SetScene("projects");
}

void EditScene::saveChanges()
{
    Project* currentProject = _projectManager.GetCurrentProject();
    _videoManager.SaveVideos(currentProject->GetProjectPath());
}

void EditScene::showVideoLibrary()
{
    _sceneManager.SetScene("gallery");
}
