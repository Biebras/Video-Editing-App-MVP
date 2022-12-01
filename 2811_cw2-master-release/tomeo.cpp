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
    window->setMinimumSize(400, 720);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    window->setLayout(mainLayout);

    //header
    QHBoxLayout* headerLayout = new QHBoxLayout();
    QWidget* headerWidget = new QWidget();
    mainLayout->addWidget(headerWidget);
    headerWidget->setLayout(headerLayout);
    headerWidget->setStyleSheet("border: 1px solid black");
    headerWidget->setMaximumHeight(window->height() * 0.08);

    //video
    QHBoxLayout* videoLayout = new QHBoxLayout();
    QWidget* videoWidget = new QWidget();
    mainLayout->addWidget(videoWidget);
    videoWidget->setLayout(videoLayout);
    videoWidget->setStyleSheet("border: 1px solid black");

    //pause
    QHBoxLayout* pauseLayout = new QHBoxLayout();
    QWidget* pauseWidget = new QWidget();
    mainLayout->addWidget(pauseWidget);
    pauseWidget->setLayout(pauseLayout);
    pauseWidget->setStyleSheet("border: 1px solid black");
    pauseWidget->setMaximumHeight(window->height() * 0.05);

    //timelapse
    QHBoxLayout* timelapseLayout = new QHBoxLayout();
    QWidget* timelapseWidget = new QWidget();
    mainLayout->addWidget(timelapseWidget);
    timelapseWidget->setLayout(timelapseLayout);
    timelapseWidget->setStyleSheet("border: 1px solid black");
    timelapseWidget->setMaximumHeight(window->height() * 0.05);

    //edit
    QHBoxLayout* editLayout = new QHBoxLayout();
    QWidget* editWidget = new QWidget();
    mainLayout->addWidget(editWidget);
    editWidget->setLayout(editLayout);
    editWidget->setStyleSheet("border: 1px solid black");
    editWidget->setMaximumHeight(window->height() * 0.2);

    //footer
    QHBoxLayout* footerLayout = new QHBoxLayout();
    QWidget* footerWidget = new QWidget();
    mainLayout->addWidget(footerWidget);
    footerWidget->setLayout(footerLayout);
    footerWidget->setStyleSheet("border: 1px solid black");
    footerWidget->setMaximumHeight(window->height() * 0.08);

    // showtime!
    window->show();

    // wait for the app to terminate
    return app.exec();
}
