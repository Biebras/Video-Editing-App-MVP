#include "videogalleryscene.h"
#include "modularlayout.h"
#include "videomanager.h"
#include "scenemanager.h"
#include <iostream>

void VideoGalleryScene::CreateWidgetsForVideoGallery()
{
    Project* currentProject = _projectManager.GetCurrentProject();
    // loop through videos if the current project is loaded
    if (currentProject)
    {
        for (int i = 0; i < currentProject->GetTotalVideos(); i++)
        {
            // create new button with thumbnail as icon if it exists
            _selectVideos.append(new QPushButton());
            _selectVideos[i]->setToolTip(tr("Select Video"));
            QString filePath = currentProject->GetVideo(i)->GetFilePath();
            QString thumbnailPath = filePath.left(filePath.length() - 4) + ".png";
            if (QFile(thumbnailPath).exists()) // if file exists
            {
                QImageReader *imageReader = new QImageReader(thumbnailPath);
                QImage sprite = imageReader->read(); // read the thumbnail image
                if (!sprite.isNull())
                {
                    _selectVideos[i]->setIcon(QIcon(QPixmap::fromImage(sprite)));
                } else
                    _selectVideos[i]->setText(tr("No thumbnail for this video"));
            } else
                _selectVideos[i]->setText(tr("No thumbnail for this video"));
        }
    }
}

void VideoGalleryScene::CreateWidgets()
{
    // header
    _backButton = new QPushButton();
    _backButton->setIcon(QIcon(":/icons/backButton.svg"));
    _backButton->setToolTip(tr("Go Back"));
    _backButton->setFixedSize(QSize(30, 30));
    _backButton->setIconSize(QSize(25, 25));
    _backButton->setStyleSheet("QPushButton {border-radius: 5px; background-color: #011502; } QPushButton:hover { background-color: #044220; }");

    _addVideos = new QPushButton();
    _addVideos->setIcon(QIcon(":icons/addIcon.svg"));
    _addVideos->setToolTip(tr("Add Video(s)"));
    _addVideos->setFixedSize(QSize(30, 30));
    _addVideos->setIconSize(QSize(25, 25));
    _addVideos->setStyleSheet("QPushButton {border-radius: 5px; background-color: #011502; } QPushButton:hover { background-color: #044220; }");

    // title
    _title = new QLabel("Video Gallery");
    _title->setAlignment(Qt::AlignCenter);
    _title->setStyleSheet("font: 10pt 'Helvetica Neue'; color: #9EC5AB; font-weight: bold;");

    // videos area

    CreateWidgetsForVideoGallery();
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
    header->GetLayoutWidget()->setStyleSheet("QWidget {background: #011502;}");

    ModularLayout* title = new ModularLayout();
    title->addWidget(_title);

    header->GetLayoutWidget()->setLayout(header);
    _mainLayout->addWidget(header->GetLayoutWidget());
    title->GetLayoutWidget()->setLayout(title);
    _mainLayout->addWidget(title->GetLayoutWidget());

    _mainLayout->setSpacing(0);
    _mainLayout->setMargin(0);

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

                _videoLayout->addWidget(_selectVideos[index], i, j);
                _selectVideos[index]->setIconSize(_selectVideos[index]->size());
            }
        }
    }

    _mainLayout->addWidget(videosLayoutWidget);
    this->setLayout(_mainLayout);
}

void VideoGalleryScene::MakeConnections()
{
    connect(_backButton, SIGNAL(clicked()), this, SLOT(GoBack()));
    connect(_addVideos, SIGNAL(clicked()), this, SLOT(FindVideos()));
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
        _selectVideos.append(new QPushButton());
        _selectVideos[i]->setToolTip(tr("Select Video"));
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
                _selectVideos[i]->setText(tr("No thumbnail for this video"));
        } else
            _selectVideos[i]->setText(tr("No thumbnail for this video"));
    }

    int cols = 2;

    if(!_sceneManager.GetWindow()->IsAppLayout)
        cols = 3;

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

            _videoLayout->addWidget(_selectVideos[index], i, j);
            _selectVideos[index]->setIconSize(_selectVideos[index]->size());
            connect(_selectVideos[index], SIGNAL(clicked()), this, SLOT(AddVideo()));
        }
    }
}

void VideoGalleryScene::Retranslate()
{
    _backButton->setToolTip(tr("Go Back"));
    _title->setText(tr("Video Gallery"));
    _addVideos->setToolTip(tr("Add Video(s)"));
}

void VideoGalleryScene::GoBack()
{
    _sceneManager.SetScene("edit");
}

void VideoGalleryScene::AddVideo()
{
    int index = _selectVideos.indexOf(qobject_cast<QPushButton* >(QObject::sender()));
    _videoManager.AddVideo(_projectManager.GetCurrentProject()->GetVideo(index));
    _sceneManager.SetScene("edit");
}

void VideoGalleryScene::FindVideos()
{
    #if defined(_WIN32)
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open File"),"/home",tr("Videos and thumbnails (*.wmv *.png)"));
    #else
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open File"),"/home",tr("Videos and thumbnails  (*.mp4 *.MOV *.png)"));
    #endif
    Project* currentProject = _projectManager.GetCurrentProject();

    foreach(auto path, fileNames)
    {
        //Copy files
        QFile file(path);
        QFileInfo fileInfo(file.fileName());
        QString copyPath = currentProject->GetProjectPath() + "/" + fileInfo.fileName();
        QFile::copy(path, copyPath);

        if(fileInfo.fileName().contains(".png"))
            continue;

        //Create video
        Video* video = new Video(copyPath, 0, 0, 1);
        currentProject->AddVideo(video);
    }

    _sceneManager.SetScene("gallery");
}
