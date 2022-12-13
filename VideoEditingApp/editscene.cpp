#include "editscene.h"
#include "modularlayout.h"
#include "scenemanager.h"
#include "videomanager.h"
#include <iostream>
#include <QDebug>

void EditScene::CreateWidgets()
{
    qDebug()<<"Edit";
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
//    _videoPlayer->SetCurrentTime(0);

    // time area
    _timeLabel = new QLabel();
    _timeLabel->setAlignment(Qt::AlignCenter);
    _timeLabel->setStyleSheet("font-size: 18pt");

    // pause/play area
    _pauseButton = new QPushButton();
    _pauseButton->setIcon(QIcon(":/icons/pauseIcon.png"));
    _pauseButton->setToolTip("Pause");
    _pauseButton->setFixedSize(QSize(50, 50));
    _volumeButton = new QPushButton();
    _volumeButton->setIcon(QIcon(":/icons/volumeIcon.png"));
    _volumeButton->setToolTip("Mute Volume");
    _volumeButton->setFixedSize(QSize(50, 50));

    // slider area
    _videoSlider = new QSlider();
    _videoSlider->setOrientation(Qt::Horizontal);
    _videoSlider->setToolTip("Move through video");

    // thumbnails
    VideoManager& videoManager = VideoManager::Get();
    // loop through videos
    //for (int i = 0; i < videoManager.GetTotalVideos(); i++)
    // for now, just three videos until videoManager properly implemented
    for (int i = 0; i < 3; i++)
    {
        _thumbnails.append(new QPushButton());
        _thumbnails[i]->setFixedHeight(80);
        _thumbnails[i]->setToolTip("Reorder Video");
        QString filePath = videoManager.GetVideo(i)->GetFilePath();
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
    _audioButton->setIcon(QIcon(":/icons/audioIcon.png"));
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

    ModularLayout* videoArea = new ModularLayout();
    videoArea->addWidget(_videoWidget);

    ModularLayout* timeArea = new ModularLayout();
    timeArea->addWidget(_timeLabel);
    timeArea->addWidget(_timeLabel);

    ModularLayout* pauseArea = new ModularLayout();
    pauseArea->addStretch();
    pauseArea->addWidget(_pauseButton);
    pauseArea->addWidget(_volumeButton);
    pauseArea->addStretch();

    ModularLayout* videoEditArea = new ModularLayout();
    videoEditArea->addWidget(_videoSlider);

    ModularLayout* thumbnailArea = new ModularLayout();
    for (auto thumbnail : _thumbnails)
    {
        thumbnailArea->addWidget(thumbnail);
    }
    thumbnailArea->setSpacing(0);

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
    videoArea->GetLayoutWidget()->setLayout(videoArea);
    timeArea->GetLayoutWidget()->setLayout(timeArea);
    pauseArea->GetLayoutWidget()->setLayout(pauseArea);
    videoEditArea->GetLayoutWidget()->setLayout(videoEditArea);
    thumbnailArea->GetLayoutWidget()->setLayout(thumbnailArea);
    reorderArea->GetLayoutWidget()->setLayout(reorderArea);
    footer->GetLayoutWidget()->setLayout(footer);

    // set each layout widget to show in the main layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(header->GetLayoutWidget());
    mainLayout->addStretch(1);
    mainLayout->addWidget(videoArea->GetLayoutWidget(), 4);
    mainLayout->addWidget(timeArea->GetLayoutWidget());
    mainLayout->addWidget(pauseArea->GetLayoutWidget());
    mainLayout->addWidget(videoEditArea->GetLayoutWidget());
    mainLayout->addWidget(thumbnailArea->GetLayoutWidget());
    mainLayout->addWidget(reorderArea->GetLayoutWidget());
    mainLayout->addWidget(footer->GetLayoutWidget());

    this->setLayout(mainLayout);
}

void EditScene::MakeConnections()
{
    /** connections:
     *  back button -> projects scene
     *  share button -> export scene
     *  add button -> video library scene
     *  pause button -> pause/play video
     *  slider -> new place in video
     *  volume button -> mute/unmute video
     *  trim button -> trim scene
     *  effect button -> fx scene
     *  audio button -> audio scene
     *  thumbnail button -> enable move left and right, if reordering enable reorder button
     *  move left -> move video pressed left one place
     *  move right -> move video pressed right one place
     *  reorder button pressed -> reorder, disable move left and right buttons
    **/

    for (auto thumbnail : _thumbnails)
        connect(thumbnail, SIGNAL(clicked()), this, SLOT(thumbnailClicked()));

    connect(_moveLeft, SIGNAL(clicked()), this, SLOT(reorderLeft()));
    connect(_moveRight, SIGNAL(clicked()), this, SLOT(reorderRight()));

    connect(_pauseButton, SIGNAL(clicked()), this, SLOT(pausePlay()));

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

    VideoManager& videoManager = VideoManager::Get();

    // swap videos
    Video* temp = videoManager.GetVideo(_reorderVideoIndex);
    videoManager.RemoveVideo(videoManager.GetVideo(_reorderVideoIndex));
    videoManager.InsertVideo(_reorderVideoIndex-1, temp);

    // swap icons
    QIcon tempIcon = _thumbnails[_reorderVideoIndex]->icon();
    _thumbnails[_reorderVideoIndex]->setIcon(_thumbnails[_reorderVideoIndex-1]->icon());
    _thumbnails[_reorderVideoIndex-1]->setIcon(tempIcon);
}

void EditScene::reorderRight()
{
    for (auto thumbnail : _thumbnails)
        thumbnail->setEnabled(true);
    _moveLeft->setEnabled(false);
    _moveRight->setEnabled(false);

    VideoManager& videoManager = VideoManager::Get();

    // swap videos
    Video* temp = videoManager.GetVideo(_reorderVideoIndex);
    videoManager.RemoveVideo(videoManager.GetVideo(_reorderVideoIndex));
    videoManager.InsertVideo(_reorderVideoIndex+1, temp);

    // swap icons
    QIcon tempIcon = _thumbnails[_reorderVideoIndex]->icon();
    _thumbnails[_reorderVideoIndex]->setIcon(_thumbnails[_reorderVideoIndex+1]->icon());
    _thumbnails[_reorderVideoIndex+1]->setIcon(tempIcon);
}

void EditScene::pausePlay()
{

}
