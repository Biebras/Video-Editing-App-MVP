//    ______
//   /_  __/___  ____ ___  ___  ____
//    / / / __ \/ __ `__ \/ _ \/ __ \
//   / / / /_/ / / / / / /  __/ /_/ /
//  /_/  \____/_/ /_/ /_/\___/\____/
//              video for sports enthusiasts...
//
//

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"
#include <QFrame>
#include <QtWidgets>
#include <string>

// read in videos and thumbnails to this directory
std::vector<TheButtonInfo> getInfoIn (std::string loc)
{

    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext())
    { // for all files

        QString f = it.next();

            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))
            { // mac/linux
#endif

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists())
            { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull())
                    {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << Qt::endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << Qt::endl;
        }
    }

    return out;
}


int main(int argc, char *argv[])
{

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder
    std::vector<TheButtonInfo> videos;
    std::cout<<argv[1]<<std::endl;

    if (argc == 2)
        videos = getInfoIn( std::string(argv[1]) );

    if (videos.size() == 0)
    {
        const int result = QMessageBox::information(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! Add command line argument to \"quoted\" file location."));
        exit(-1);
    }


    // the widget that will show the video
    QVideoWidget *videoWidget = new QVideoWidget;



    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    // setNotifyInterval sets the time at which the player updates
    player->setNotifyInterval(100);


    player->setVideoOutput(videoWidget);

    // set details of the pause button
    player->pauseButton.setIcon(QIcon(":/pauseIcon.png"));
    player->pauseButton.setToolTip("Pause");
    player->pauseButton.setFixedSize(QSize(50, 50));

    // initialise the timer label
    player->timeLabel = new QLabel();
    player->timeLabel->setAlignment(Qt::AlignCenter);
    player->timeLabel->setStyleSheet("font-size: 18pt");

    //player->videoSlider = new QSlider(Qt::Horizontal);
    player->videoSlider.setOrientation(Qt::Horizontal);
    player->videoSlider.setToolTip("Move through video");
    //player->videoSlider->setMaximum(10);
    //std::cout << player->duration()/1000;



    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    std::vector<TheButton*> buttons;


    // create the four buttons
    for ( int i = 0; i < 4; i++ )
    {
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
        buttons.push_back(button);
        button->init(&videos.at(i));
    }

    // tell the player what buttons and videos are available
    player->setContent(&buttons, &videos);

    //player->videoSlider->setMaximum(player->duration()/1000);

    // create the main window and layout
    QWidget *window = new QWidget();
    //QVBoxLayout *top = new QVBoxLayout();
    //window.setLayout(top);
    window->setWindowTitle("tomeo");
    window->setMinimumSize(400, 720);

    QVBoxLayout* _mainLayout = new QVBoxLayout(window);

    // create all the widgets
    QPushButton* backButton = new QPushButton();
    backButton->setIcon(QIcon(":/backIcon.png"));
    backButton->setToolTip("Go Back");
    backButton->setFixedSize(QSize(50,50));
    QPushButton* shareButton = new QPushButton();
    shareButton->setIcon(QIcon(":/shareIcon.png"));
    shareButton->setToolTip("Share");
    shareButton->setFixedSize(QSize(50, 50));
    QPushButton* addButton = new QPushButton();
    addButton->setIcon(QIcon(":/addIcon.png"));
    addButton->setToolTip("Add Video");
    addButton->setFixedSize(QSize(50,50));
//    QSlider* videoSlider = new QSlider(Qt::Horizontal);
//    player->videoSlider = new QSlider(Qt::Horizontal);
//    player->videoSlider->setToolTip("Move through video");
    QPushButton* trimButton = new QPushButton();
    trimButton->setIcon(QIcon(":/trimIcon.png"));
    trimButton->setToolTip("Trim Video");
    trimButton->setFixedSize(QSize(50, 50));
    QPushButton* effectButton = new QPushButton();
    effectButton->setIcon(QIcon(":/effectIcon.png"));
    effectButton->setToolTip("Add Effects");
    effectButton->setFixedSize(QSize(50, 50));
    QPushButton* audioButton = new QPushButton();
    audioButton->setIcon(QIcon(":/audioIcon.png"));
    audioButton->setToolTip("Add Audio");
    audioButton->setFixedSize(QSize(50, 50));


    // layouts for each box
    QHBoxLayout* header = new QHBoxLayout();
    header->addWidget(backButton);
    header->addStretch();
    header->addWidget(shareButton);
    header->addWidget(addButton);
    QHBoxLayout* videoArea = new QHBoxLayout();
    videoArea->addWidget(videoWidget);
    QHBoxLayout* timeArea = new QHBoxLayout();
    timeArea->addWidget(player->timeLabel);
    QHBoxLayout* pauseArea = new QHBoxLayout();
    pauseArea->addStretch();
    pauseArea->addWidget(&(player->pauseButton));
    pauseArea->addStretch();
    QHBoxLayout* videoEditArea = new QHBoxLayout();
    videoEditArea->addWidget(&player->videoSlider);
    QHBoxLayout* footer = new QHBoxLayout();
    footer->addStretch();
    footer->addWidget(trimButton);
    footer->addWidget(effectButton);
    footer->addWidget(audioButton);
    footer->addStretch();

    // put all the layouts in a corresponding group box
    QGroupBox* headerBox = new QGroupBox();
    headerBox->setLayout(header);
    QGroupBox* videoBox = new QGroupBox();
    videoBox->setLayout(videoArea);
    QGroupBox* timeBox = new QGroupBox();
    timeBox->setLayout(timeArea);
    QGroupBox* pauseBox = new QGroupBox();
    pauseBox->setLayout(pauseArea);
    QGroupBox* videoEditBox = new QGroupBox();
    videoEditBox->setLayout(videoEditArea);
    QGroupBox* footerBox = new QGroupBox();
    footerBox->setLayout(footer);

    // add each group box to the main layout
    _mainLayout->addWidget(headerBox);
    _mainLayout->addStretch(1);
    _mainLayout->addWidget(videoBox, 4);
    _mainLayout->addWidget(timeBox);
    _mainLayout->addWidget(pauseBox);
    _mainLayout->addWidget(videoEditBox);
    _mainLayout->addStretch(1);
    _mainLayout->addWidget(footerBox);


    // add the video and the buttons to the top level widget
    //top->addWidget(videoWidget);
    //top->addWidget(buttonWidget);

    // showtime!
    window->show();

    // wait for the app to terminate
    return app.exec();
}
