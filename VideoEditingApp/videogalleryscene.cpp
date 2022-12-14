#include "videogalleryscene.h"
#include "modularlayout.h"
#include "videomanager.h"
#include "scenemanager.h"
#include <iostream>

void VideoGalleryScene::CreateWidgets()
{
    // header
    _backButton = new QPushButton();
    _backButton->setIcon(QIcon(":/icons/backIcon.png"));
    _backButton->setToolTip("Go Back");
    _backButton->setFixedSize(QSize(50, 50));
    _backButton->setStyleSheet("QPushButton { border: 1px solid #104F55; border-radius: 5px; background-color: #9EC5AB; } QPushButton:hover { background-color: #FCEA4D; }");
    _title = new QLabel("Video Gallery");
    _title->setAlignment(Qt::AlignCenter);
    _title->setStyleSheet("font: 20pt 'Helvetica Neue'; color: #FCEA4D; font-weight: bold;");
    _addVideos = new QPushButton();
    _addVideos->setIcon(QIcon(":icons/addIcon.png"));
    _addVideos->setToolTip("Add Video(s)");
    _addVideos->setFixedSize(QSize(50, 50));
    _addVideos->setStyleSheet("QPushButton { border: 1px solid #104F55; border-radius: 5px; background-color: #9EC5AB; } QPushButton:hover { background-color: #FCEA4D; }");
}

void VideoGalleryScene::ArrangeWidgets()
{
    _mainLayout = new QVBoxLayout();
    _mainLayout->setAlignment(Qt::AlignTop);


    // create layouts for each area
    ModularLayout* header = new ModularLayout();
    header->addWidget(_backButton);
    header->addStretch();
    header->addWidget(_title);
    header->addStretch();
    header->addWidget(_addVideos);


    header->GetLayoutWidget()->setLayout(header);
    _mainLayout->addWidget(header->GetLayoutWidget());

    // get the window widget
    SceneManager& sceneManager = SceneManager::Get();

    //videos layout
    QWidget* videosLayoutWidget = new QWidget();
    videosLayoutWidget->setLayout(_videoLayout);

    if (_selectVideos.size() > 0)
    {
        int cols = 2;
        int rows = _selectVideos.size() / cols + _selectVideos.size() % 2;

        // create new ModularLayout for each row and add to mainLayout
        for (int i = 0; i < rows; i++)
        {
            //ModularLayout *videoRow = new ModularLayout();
            for (int j = 0; j < cols; j++)
            {
                int index = i * cols + j;

                if(index >= _selectVideos.size())
                    break;

                _videoLayout->addWidget(_selectVideos[index]);
                _selectVideos[index]->setIconSize(_selectVideos[index]->size());
            }
        }
    }

    _mainLayout->addWidget(videosLayoutWidget);
    this->setLayout(_mainLayout);
}

void VideoGalleryScene::MakeConnections()
{
    /** connections:
     *  recalculate no. rows when screen size changes
     *  back button -> projects scene
     *  video selected -> highlight widget
     *  add video button -> edit scene, load videos
     **/

    connect(_backButton, SIGNAL(clicked()), this, SLOT(GoBack()));

    foreach(auto button, _selectVideos)
        connect(button, SIGNAL(clicked()), this, SLOT(AddVideo()));
}

void VideoGalleryScene::UpdateScene()
{
    Project* currentProject = _projectManager.GetCurrentProject();

    while (_videoLayout->count() > 0)
    {
        QWidget *w = _videoLayout->takeAt(0)->widget();

        if (w)
        {
            w->deleteLater();
        }
    }

    _selectVideos.clear();

    for (int i = 0; i < currentProject->GetTotalVideos(); i++)
    {
        Video* video = currentProject->GetVideo(i);
        QPushButton* button = new QPushButton();
        _selectVideos.append(button);
        _selectVideos[i]->setToolTip("Select Video");
        QString filePath = currentProject->GetVideo(i)->GetFilePath();
        QString thumbnailPath = filePath.left(filePath.length() - 4) + ".png";
        if (QFile(thumbnailPath).exists()) // if file exists
        {
            QImageReader *imageReader = new QImageReader(thumbnailPath);
            QImage sprite = imageReader->read(); // read the thumbnail image
            if (!sprite.isNull())
            {
                _selectVideos[i]->setIcon(QIcon(QPixmap::fromImage(sprite)));
                _selectVideos[i]->setIconSize(_selectVideos[i]->size());

            } else
                _selectVideos[i]->setText("No thumbnail for this video");
        } else
            _selectVideos[i]->setText("No thumbnail for this video");

        _videoLayout->addWidget(_selectVideos[i]);
        connect(button, &QPushButton::clicked, [video]
        {
            VideoManager& _videoManager = VideoManager::Get();
            SceneManager& _sceneManager = SceneManager::Get();
            _videoManager.AddVideo(video);
            _sceneManager.SetScene("edit");
        });
    }
}

void VideoGalleryScene::GoBack()
{
    _sceneManager.SetScene("edit");
}
