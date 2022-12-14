#include "createprojectscene.h"
#include "modularlayout.h"

void CreateProjectScene::CreateWidgets()
{
    // disabled header
    _title = new QLabel("My Projects");
    _title->setAlignment(Qt::AlignCenter);
    _title->setStyleSheet("font: 30pt 'Helvetica Neue'; color: #FCEA4D; font-weight: bold;");
    _title->setEnabled(false);
    _addProject = new QPushButton();
    _addProject->setIcon(QIcon(":icons/addIcon.png"));
    _addProject->setToolTip("Create Project");
    _addProject->setFixedSize(QSize(50, 50));
    _addProject->setStyleSheet("QPushButton { border: 1px solid #104F55; border-radius: 5px; background-color: #9EC5AB; } QPushButton:hover { background-color: #FCEA4D; }");
    _addProject->setEnabled(false);

    // input
    _nameLabel = new QLabel("Project Name: ");
    _nameLabel->setStyleSheet("font-size: 20pt; color: #9EC5AB;");
    _nameInput = new QLineEdit();
    _nameInput->setStyleSheet("font-size: 18px; padding: 5px; background-color: #32746D;");

    // button
    _createProject = new QPushButton("Create Project");
    _createProject->setToolTip("Create Project");
    _createProject->setStyleSheet("QPushButton { border: 1px solid #104F55; border-radius: 5px; font-size: 18px; padding: 10px; background-color: #9EC5AB; } QPushButton:hover { background-color: #FCEA4D; }");
}

void CreateProjectScene::ArrangeWidgets()
{
    QVBoxLayout* mainLayout = new QVBoxLayout();

    // layout for disabled header
    ModularLayout* header = new ModularLayout();
    header->addStretch();
    header->addWidget(_title);
    header->addStretch();
    header->addWidget(_addProject);
    //header->setEnabled(true);

    // layout for input
    ModularLayout* inputLayout = new ModularLayout();
    inputLayout->addStretch();
    inputLayout->addWidget(_nameLabel);
    inputLayout->addWidget(_nameInput);
    inputLayout->addStretch();

    //layout for button
    ModularLayout* buttonLayout = new ModularLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(_createProject);
    buttonLayout->addStretch();

    header->GetLayoutWidget()->setLayout(header);
    inputLayout->GetLayoutWidget()->setLayout(inputLayout);
    buttonLayout->GetLayoutWidget()->setLayout(buttonLayout);

    // create a group box for the input and create project button
    QVBoxLayout* inputBoxLayout = new QVBoxLayout();
    inputBoxLayout->addWidget(inputLayout->GetLayoutWidget());
    inputBoxLayout->addWidget(buttonLayout->GetLayoutWidget());

    QGroupBox* inputBox = new QGroupBox();
    inputBox->setLayout(inputBoxLayout);

    mainLayout->addWidget(header->GetLayoutWidget());
    mainLayout->addStretch();
    mainLayout->addWidget(inputBox);
    mainLayout->addStretch();

    this->setLayout(mainLayout);
}

void CreateProjectScene::MakeConnections()
{
    connect(_createProject, SIGNAL(clicked()), this, SLOT(CreateProject()));
    /** connections:
     *  create project button -> edit scene, store project name somewhere?
     **/
}

void CreateProjectScene::CreateProject()
{
    _projectManager.CreateProject(_nameInput->text());

    _sceneManager.SetScene("projects");
}
