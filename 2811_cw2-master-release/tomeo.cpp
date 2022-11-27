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

    /*
    // the widget that will show the video
    QVideoWidget *videoWidget = new QVideoWidget;

    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);

    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    std::vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QHBoxLayout *layout = new QHBoxLayout();
    buttonWidget->setLayout(layout);


    // create the four buttons
    for ( int i = 0; i < 4; i++ )
    {
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
        buttons.push_back(button);
        layout->addWidget(button);
        button->init(&videos.at(i));
    }

    // tell the player what buttons and videos are available
    player->setContent(&buttons, &videos);
    */

    // create the main window and layout
    QWidget *window = new QWidget();
    //QVBoxLayout *top = new QVBoxLayout();
    //window.setLayout(top);
    window->setWindowTitle("tomeo");
    //window->setMinimumSize(400, 720);

    // the buttons are arranged horizontally
//    QGridLayout* gridLayout = new QGridLayout(window);
//    QHBoxLayout* header = new QHBoxLayout(window);
//    QHBoxLayout* videoArea = new QHBoxLayout(window);
//    QHBoxLayout* timeArea = new QHBoxLayout(window);
//    QHBoxLayout* pauseArea = new QHBoxLayout(window);
//    QHBoxLayout* videoEditingArea = new QHBoxLayout(window);
//    QHBoxLayout* footer = new QHBoxLayout(window);

//    gridLayout->addLayout(header, 0, 0);
//    gridLayout->addLayout(videoArea, 1, 0);
//    gridLayout->addLayout(timeArea, 2, 0);
//    gridLayout->addLayout(pauseArea, 3, 0);
//    gridLayout->addLayout(videoEditingArea, 4, 0);
//    gridLayout->addLayout(footer, 5, 0);

//    header->

//    QFrame *label = new QFrame();
//    QFrame *label2 = new QFrame();
//    QFrame *label3 = new QFrame();
//    QFrame *label4 = new QFrame();
//    QFrame *label5 = new QFrame();
//    QFrame *label6 = new QFrame();

//    label->setLineWidth(2);
//    label->setFrameStyle(QFrame::Panel);
//    label2->setLineWidth(2);
//    label2->setFrameStyle(QFrame::Panel);
//    label3->setLineWidth(2);
//    label3->setFrameStyle(QFrame::Panel);
//    label4->setLineWidth(2);
//    label4->setFrameStyle(QFrame::Panel);
//    label5->setLineWidth(2);
//    label5->setFrameStyle(QFrame::Panel);
//    label6->setLineWidth(2);
//    label6->setFrameStyle(QFrame::Panel);

//    header->addWidget(label);
//    videoArea->addWidget(label2);
//    timeArea->addWidget(label3);
//    pauseArea->addWidget(label4);
//    videoEditingArea->addWidget(label5);
//    footer->addWidget(label6);

    QVBoxLayout* _mainLayout = new QVBoxLayout(window);
    QHBoxLayout* header = new QHBoxLayout();
    QHBoxLayout* videoArea = new QHBoxLayout(window);
    QHBoxLayout* timeArea = new QHBoxLayout(window);

    _mainLayout->addLayout(header);
    _mainLayout->addLayout(videoArea);
    _mainLayout->addLayout(timeArea);

    QPushButton* button = new QPushButton("Header");
    button->setGeometry(*new QRect(0, 0, window->width(), 10));
    QPushButton* button1 = new QPushButton("Video Area");
    QPushButton* button2 = new QPushButton("Time Area");

    header->addWidget(button);
    videoArea->addWidget(button1);
    timeArea->addWidget(button2);

    // add the video and the buttons to the top level widget
    //top->addWidget(videoWidget);
    //top->addWidget(buttonWidget);

    // showtime!
    window->show();

    // wait for the app to terminate
    return app.exec();
}
