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
    _title = new QLabel("Video Gallery");
    _title->setAlignment(Qt::AlignCenter);
    _title->setStyleSheet("font-size: 18pt");
    _addVideos = new QPushButton();
    _addVideos->setIcon(QIcon(":icons/addIcon.png"));
    _addVideos->setToolTip("Add Video(s)");
    _addVideos->setFixedSize(QSize(50, 50));

    // videos area
    VideoManager& videoManager = VideoManager::Get();

    //Video* vid = videoManager.GetVideo(1);

    for (int i = 0; i < videoManager.GetTotalVideos(); i++) {
        _selectVideos.append(new QPushButton());
        _selectVideos[i]->setToolTip("Select Video");
        QString filePath = QString::fromStdString(videoManager.GetVideo(i)->GetFilePath());
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
    }
}

void VideoGalleryScene::ArrangeWidgets()
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignTop);


    // create layouts for each area
    ModularLayout* header = new ModularLayout();
    header->addWidget(_backButton);
    header->addStretch();
    header->addWidget(_title);
    header->addStretch();
    header->addWidget(_addVideos);



    header->GetLayoutWidget()->setLayout(header);
    mainLayout->addWidget(header->GetLayoutWidget());

    // get the window widget
    SceneManager& sceneManager = SceneManager::Get(nullptr);
    QWidget* window = sceneManager.GetWindow();

    // assuming buttons should be no less than 200 wide
    int itemsPerRow = floor(float(window->width()) / 200.0);
    int rows = ceil(float(_selectVideos.size()) / float(itemsPerRow));
    int itemsLast = _selectVideos.size() - (rows-1)*itemsPerRow; //no. items on last row
    int it = 0;

    // create new ModularLayout for each row and add to mainLayout
    for (int i = 0; i < rows - 1; i++)
    {
        ModularLayout *videoRow = new ModularLayout();
        for (int j = 0; j < itemsPerRow; j++)
        {
            videoRow->addWidget(_selectVideos[it]);
            it ++;
        }
        videoRow->GetLayoutWidget()->setLayout(videoRow);
        mainLayout->addWidget(videoRow->GetLayoutWidget());
    }

    // last row of videos
    ModularLayout *videoRow = new ModularLayout();
    for (int i = 0; i < itemsLast; i++)
    {
        videoRow->addWidget(_selectVideos[it]);
        it ++;
    }

    // add empty labels to take up space remaning on last row
    QLabel* space = new QLabel();
    for (int i = 0; i < itemsPerRow-itemsLast; i++)
    {
        videoRow->addWidget(space);
    }
    videoRow->GetLayoutWidget()->setLayout(videoRow);
    mainLayout->addWidget(videoRow->GetLayoutWidget());

    this->setLayout(mainLayout);
}

void VideoGalleryScene::MakeConnections()
{
    /** connections:
     *  recalculate no. rows when screen size changes
     *  back button -> projects scene
     *  video selected -> highlight widget
     *  add video button -> edit scene, load videos
     **/
}
