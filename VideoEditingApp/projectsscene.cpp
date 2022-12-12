#include "projectsscene.h"
#include "modularlayout.h"

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
}

void ProjectsScene::ArrangeWidgets()
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignTop);

    // layout for header
    ModularLayout* header = new ModularLayout();
    header->addStretch();
    header->addWidget(_title);
    header->addStretch();
    header->addWidget(_addProject);

    header->GetLayoutWidget()->setLayout(header);
    mainLayout->addWidget(header->GetLayoutWidget());
    this->setLayout(mainLayout);
}

void ProjectsScene::MakeConnections()
{
    /** connections:
     *  add project button -> create project scene
     **/
}
