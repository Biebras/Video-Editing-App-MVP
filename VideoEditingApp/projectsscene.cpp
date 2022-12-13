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
        qDebug() << project->GetProjectName();
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

    _mainLayout->addWidget(header->GetLayoutWidget());

    //projects layout
    foreach(auto button, _projectButtons)
    {
            ModularLayout* projectLayout = new ModularLayout();
            projectLayout->addWidget(button);
            _mainLayout->addWidget(projectLayout->GetLayoutWidget());
    }

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

}

void ProjectsScene::ChangeSceneToCreateProject()
{
    _sceneManager.SetScene("createProject");
}


