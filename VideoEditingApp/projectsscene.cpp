#include "projectsscene.h"
#include "modularlayout.h"
#include <QDebug>
#include "videomanager.h"

void ProjectsScene::CreateWidgets()
{
    // header
    _title = new QLabel("My Projects");
    _title->setAlignment(Qt::AlignCenter);
    _title->setStyleSheet("font: 30pt 'Helvetica Neue'; color: #FCEA4D; font-weight: bold;");
    _addProject = new QPushButton();
    _addProject->setIcon(QIcon(":icons/addIcon.png"));
    _addProject->setToolTip("Create Project");
    _addProject->setFixedSize(QSize(50, 50));
    _addProject->setStyleSheet("QPushButton { border: 1px solid #104F55; border-radius: 5px; background-color: #9EC5AB; } QPushButton:hover { background-color: #FCEA4D; }");
}

void ProjectsScene::ArrangeWidgets()
{
    _mainLayout->setAlignment(Qt::AlignTop);
    _projectsLayout = new QVBoxLayout();
    // layout for header
    ModularLayout* header = new ModularLayout();
    header->addStretch();
    header->addWidget(_title);
    header->addStretch();
    header->addWidget(_addProject);

    //projects layout
    QWidget* projectsLayoutWidget = new QWidget();
    projectsLayoutWidget->setLayout(_projectsLayout);

    _mainLayout->addWidget(header->GetLayoutWidget());
    _mainLayout->addWidget(projectsLayoutWidget);

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
        _projectButtons.push_back(projectButton);
        _projectsLayout->addWidget(projectButton);
        projectButton->setStyleSheet("QPushButton { border: 1px solid #104F55; border-radius: 5px; height: 50px; background-color: #9EC5AB; } QPushButton:hover { background-color: #FCEA4D; }");
        //connect(projectButton, SIGNAL(clicked()), this, SLOT(ChangeSceneToEdit()));

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


