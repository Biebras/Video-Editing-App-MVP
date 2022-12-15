#include "projectsscene.h"
#include "modularlayout.h"
#include <QDebug>
#include "videomanager.h"

void ProjectsScene::CreateWidgets()
{
    // header
    _english = new QPushButton();
    _english->setFixedSize(QSize(30, 30));
    _english->setStyleSheet("QPushButton {border-radius: 5px; background-color: #011502; } QPushButton:hover { background-color: #044220; }");
    _english->setIcon(QIcon(":icons/united-kingdom.png"));
    _english->setIconSize(QSize(25, 25));
    _english->setToolTip(tr("Eanglish Language"));
    _franch = new QPushButton();
    _franch->setFixedSize(QSize(30, 30));
    _franch->setStyleSheet("QPushButton {border-radius: 5px; background-color: #011502; } QPushButton:hover { background-color: #044220; }");
    _franch->setIcon(QIcon(":icons/france.png"));
    _franch->setIconSize(QSize(25, 25));
    _franch->setToolTip(tr("French Language"));
    _cat = new QPushButton();
    _cat->setFixedSize(QSize(30, 30));
    _cat->setStyleSheet("QPushButton {border-radius: 5px; background-color: #011502; } QPushButton:hover { background-color: #044220; }");
    _cat->setIcon(QIcon(":icons/kitty.png"));
    _cat->setIconSize(QSize(25, 25));
    _cat->setToolTip(tr("Cat Language"));
    _addProject = new QPushButton();
    _addProject->setIcon(QIcon(":icons/addIcon.svg"));
    _addProject->setToolTip(tr("Create Project"));
    _addProject->setFixedSize(QSize(30, 30));
    _addProject->setIconSize(QSize(30, 30));
    _addProject->setStyleSheet("QPushButton {border-radius: 5px; background-color: #011502; } QPushButton:hover { background-color: #044220; }");

    // title
    _title = new QLabel(tr("My Projects"));
    _title->setAlignment(Qt::AlignCenter);
    _title->setFixedHeight(30);
    _title->setStyleSheet("font: 10pt 'Helvetica Neue'; color: #9EC5AB; font-weight: bold;");

}

void ProjectsScene::ArrangeWidgets()
{
    _mainLayout->setAlignment(Qt::AlignTop);
    _projectsLayout = new QVBoxLayout();

    // layout for header
    ModularLayout* header = new ModularLayout();
    header->addStretch();
    header->addWidget(_english);
    header->addWidget(_franch);
    header->addWidget(_cat);
    header->addWidget(_addProject);
    header->GetLayoutWidget()->setStyleSheet("QWidget {background: #011502;}");


    // layout for title
    ModularLayout* title = new ModularLayout();
    title->addStretch();
    title->addWidget(_title);
    title->addStretch();

    title->GetLayoutWidget()->setLayout(title);

    
    QPushButton* projectButton = new QPushButton(tr("projectName"));
    _projectsLayout->addWidget(projectButton);

    _mainLayout->addWidget(header->GetLayoutWidget());
    _mainLayout->addWidget(title->GetLayoutWidget());

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* projectsLayoutWidget = new QWidget();
    _mainLayout->addWidget(scrollArea);
    scrollArea->setWidget(projectsLayoutWidget);
    projectsLayoutWidget->setLayout(_projectsLayout);

    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    _mainLayout->setSpacing(0);
    _mainLayout->setMargin(0);

    this->setLayout(_mainLayout);
}

void ProjectsScene::MakeConnections()
{ 
    connect(_addProject, SIGNAL(clicked()), this, SLOT(ChangeSceneToCreateProject()));
    //connect(_english, SIGNAL(clicked()), this, SLOT(ChangeLanToEn()));
    //connect(_franch, SIGNAL(clicked()), this, SLOT(ChangeLanToFr()));
    connect(_cat, SIGNAL(clicked()), this, SLOT(ChangeLanToCat()));
    /** connections:
     *  add project button -> create project scene
     **/
}

void ProjectsScene::UpdateScene()
{

    while (_projectsLayout->count() > 0)
    {
        QWidget *w = _projectsLayout->takeAt(0)->widget();

        if (w)
        {
            delete w;
        }
    }

    _projectButtons.clear();


    foreach(auto project, _projectManager.GetProjects())
    {
        QString projectName =  project->GetProjectName();
        QPushButton* projectButton = new QPushButton(projectName);
        projectButton->setFixedHeight(100);
        projectButton->setToolTip("Select Project");
        _projectButtons.push_back(projectButton);
        _projectsLayout->addWidget(projectButton);
        projectButton->setStyleSheet("QPushButton { border: 1px solid #104F55; border-radius: 5px; height: 50px; background-color: #9EC5AB; } QPushButton:hover { background-color: #FCEA4D; }");

        connect(projectButton, &QPushButton::clicked, [project]()
        {
            ProjectManager& _projectManager = ProjectManager::Get();
            SceneManager& _sceneManager = SceneManager::Get();
            VideoManager& _videoManager = VideoManager::Get();
            _projectManager.SetCurrentProject(project);
            _videoManager.LoadVideos(project->GetProjectPath());
            _sceneManager.SetScene("edit");
        });
    }

}

void ProjectsScene::ChangeSceneToCreateProject()
{
    _sceneManager.SetScene("createProject");
}

void ProjectsScene::ChangeLanToEn()
{
    //qApp->removeTranslator(&transl)
}

void ProjectsScene::ChangeLanToFr()
{
    //_sceneManager.SetScene("createProject");
}

void ProjectsScene::ChangeLanToCat()
{

}
