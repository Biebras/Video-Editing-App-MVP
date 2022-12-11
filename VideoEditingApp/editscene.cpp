#include "editscene.h"
#include "modularlayout.h"
#include <iostream>

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

    // time area
    _timeLabel = new QLabel();
    _timeLabel->setAlignment(Qt::AlignCenter);
    _timeLabel->setStyleSheet("font-size: 18pt");

    // pause/play area
    _pauseButton = new QPushButton();
    _pauseButton->setIcon(QIcon(":/icons/pauseIcon.png"));
    _pauseButton->setToolTip("Pause");
    _pauseButton->setFixedSize(QSize(50, 50));

    // slider area
    _videoSlider = new QSlider();
    _videoSlider->setOrientation(Qt::Horizontal);
    _videoSlider->setToolTip("Move through video");

    // volume area
    _volumeButton = new QPushButton();
    _volumeButton->setIcon(QIcon(":/icons/volumeIcon.png"));
    _volumeButton->setToolTip("Mute Volume");
    _volumeButton->setFixedSize(QSize(50, 50));

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
    pauseArea->addStretch();

    ModularLayout* videoEditArea = new ModularLayout();
    videoEditArea->addWidget(_videoSlider);

    ModularLayout* volumeArea = new ModularLayout();
    volumeArea->addStretch();
    volumeArea->addWidget(_volumeButton);
    volumeArea->addStretch();

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
    volumeArea->GetLayoutWidget()->setLayout(volumeArea);
    footer->GetLayoutWidget()->setLayout(footer);

    // set each layout widget to show in the main layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(header->GetLayoutWidget());
    mainLayout->addStretch(1);
    mainLayout->addWidget(videoArea->GetLayoutWidget(), 4);
    mainLayout->addWidget(timeArea->GetLayoutWidget());
    mainLayout->addWidget(pauseArea->GetLayoutWidget());
    mainLayout->addWidget(videoEditArea->GetLayoutWidget());
    mainLayout->addWidget(volumeArea->GetLayoutWidget());
    mainLayout->addStretch(1);
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
    **/
}
