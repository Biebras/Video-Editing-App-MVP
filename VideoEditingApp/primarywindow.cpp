#include "primarywindow.h"
#include <QDebug>
#include "scenemanager.h"

PrimaryWindow::PrimaryWindow()
{
    //set window background colour
    setWindowTitle("App");
    setMinimumSize(400, 720);
    resize(minimumSize());
    setStyleSheet("background-color: #01200F;");
    QWidget* centerWidget = new QWidget();
    setCentralWidget(centerWidget);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #000000; border: 0px; }");
    CreateMenuWindow();
}

void PrimaryWindow::resizeEvent(QResizeEvent *event)
{
    if(IsAppLayout && size().width() > AppLayoutMaxX)
    {
        SceneManager& _sceneManager = SceneManager::Get();
        IsAppLayout = false;
        _sceneManager.UpdateCurrentScene();
    }
    else if (!IsAppLayout && size().width() < AppLayoutMaxX)
    {
        SceneManager& _sceneManager = SceneManager::Get();
        IsAppLayout = true;
        _sceneManager.UpdateCurrentScene();
    }
}

void PrimaryWindow::LoadLanguage(const QString &rLanguage)
{

}

void PrimaryWindow::CreateMenuWindow()
{
    QMenuBar* menuBar = new QMenuBar();
    setMenuBar(menuBar);
    menuBar->setStyleSheet("background-color: red;");

    QMenu* menu = new QMenu("Languages");
    menuBar->addMenu(menu);

    QAction* catAction = new QAction("Cat");
    QAction* englishAction = new QAction("Eanglish");
    QAction* frenchAction = new QAction("French");

    menu->addAction(englishAction);
    menu->addAction(frenchAction);
    menu->addAction(catAction);
}

void PrimaryWindow::CreateLanguageMenu(void)
{
    //QActionGroup* langGroup = new QActionGroup(ui.menuLanguage);
   // langGroup->setExclusive(true);
}
