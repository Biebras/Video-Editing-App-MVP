#include "projectsscene.h"
#include "modularlayout.h"
#include <QDebug>

void ProjectsScene::CreateWidgets()
{
    // header
    _title = new QLabel("My Projects");
    _title->setAlignment(Qt::AlignCenter);
    _title->setStyleSheet("font-size: 18pt");
    _addProject = new QPushButton();
    _addProject->setIcon(QIcon(":icons/addIcon.png"));
    _addProject->setToolTip("Create Project");
    _addProject->setFixedSize(QSize(50, 50));

    //projects
    foreach(auto project, _projectManager.GetProjects())
    {
        QPushButton* projectButton = new QPushButton(project->GetProjectName());
        _projectButtons.push_back(projectButton);
    }
}

void ProjectsScene::ArrangeWidgets()
{
    _mainLayout->setAlignment(Qt::AlignTop);

    // layout for header
    ModularLayout* header = new ModularLayout();
    header->addStretch();
    header->addWidget(_title);
    header->addStretch();
    header->addWidget(_addProject);

    //projects layout
    QWidget* projectsLayoutWidget = new QWidget();
    projectsLayoutWidget->setLayout(_projectsLayout);

    foreach(auto button, _projectButtons)
    {
            _projectsLayout->addWidget(button);
    }

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
            w->deleteLater();
        }
    }

    _projectButtons.clear();

    foreach(auto project, _projectManager.GetProjects())
    {
        QString projectName =  project->GetProjectName();
        QPushButton* projectButton = new QPushButton(projectName);
        _projectButtons.push_back(projectButton);
        _projectsLayout->addWidget(projectButton);
        //connect(projectButton, SIGNAL(clicked()), this, SLOT(ChangeSceneToEdit()));

        connect(projectButton, &QPushButton::clicked, [project]()
        {
            ProjectManager& _projectManager = ProjectManager::Get();
            SceneManager& _sceneManager = SceneManager::Get();
            _projectManager.SetCurrentProject(project);
            _sceneManager.SetScene("edit");
        });
    }
}

void ProjectsScene::ChangeSceneToCreateProject()
{
    _sceneManager.SetScene("createProject");
}


