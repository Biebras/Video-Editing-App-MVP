#include "projectsscene.h"
#include "modularlayout.h"
#include <QDebug>
#include "videomanager.h"

void ProjectsScene::CreateWidgets()
{
    // header
    _addProject = new QPushButton();
    _addProject->setIcon(QIcon(":icons/addIcon.png"));
    _addProject->setToolTip(tr("Create Project"));
    _addProject->setFixedSize(QSize(50, 50));
    _addProject->setStyleSheet("QPushButton { border: 1px solid #104F55; border-radius: 5px; background-color: #9EC5AB; } QPushButton:hover { background-color: #FCEA4D; }");

    // title
    _title = new QLabel("My Projects");
    _title->setAlignment(Qt::AlignCenter);
    _title->setStyleSheet("font: 30pt 'Helvetica Neue'; color: #FCEA4D; font-weight: bold;");
}

void ProjectsScene::ArrangeWidgets()
{
    _mainLayout->setAlignment(Qt::AlignTop);
    _projectsLayout = new QVBoxLayout();

    // layout for header
    ModularLayout* header = new ModularLayout();
    header->addStretch();
    header->addWidget(_addProject);
    header->GetLayoutWidget()->setStyleSheet("QWidget {background: #011502;}");
    header->setSpacing(0);
    header->setMargin(0);

    // layout for title
    ModularLayout* title = new ModularLayout();
    title->addStretch();
    title->addWidget(_title);
    title->addStretch();

    //projects layout
    QWidget* projectsLayoutWidget = new QWidget();
    projectsLayoutWidget->setLayout(_projectsLayout);


    title->GetLayoutWidget()->setLayout(title);
    
    QPushButton* projectButton = new QPushButton(tr("projectName"));
    _projectsLayout->addWidget(projectButton);

    _mainLayout->addWidget(header->GetLayoutWidget());
    _mainLayout->addWidget(title->GetLayoutWidget());
    _mainLayout->addWidget(projectsLayoutWidget);

    _mainLayout->setSpacing(0);
    _mainLayout->setMargin(0);

    this->setLayout(_mainLayout);
}

void ProjectsScene::MakeConnections()
{ 
    connect(_addProject, SIGNAL(clicked()), this, SLOT(ChangeSceneToCreateProject()));
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


