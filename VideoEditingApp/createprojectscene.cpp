#include "createprojectscene.h"
#include "modularlayout.h"

void CreateProjectScene::CreateWidgets()
{
    // back button
    _backButton = new QPushButton();
    _backButton->setIcon(QIcon(":/icons/backButton.svg"));
    _backButton->setToolTip(tr("Go Back"));
    _backButton->setFixedSize(QSize(30, 30));
    _backButton->setIconSize(QSize(25, 25));
    _backButton->setStyleSheet("QPushButton {border-radius: 5px; background-color: #011502; } QPushButton:hover { background-color: #044220; }");

    // input
    _nameLabel = new QLabel(tr("Project Name: "));
    _nameLabel->setStyleSheet("font-size: 20pt; color: #9EC5AB;");
    _nameInput = new QLineEdit();
    _nameInput->setStyleSheet("font-size: 18px; padding: 5px; background-color: #32746D;");

    // button
    _createProject = new QPushButton(tr("Create Project"));
    _createProject->setToolTip(tr("Create Project"));
    _createProject->setStyleSheet("QPushButton { border: 1px solid #104F55; border-radius: 5px; font-size: 18px; padding: 10px; background-color: #9EC5AB; } QPushButton:hover { background-color: #FCEA4D; }");
}

void CreateProjectScene::ArrangeWidgets()
{
    // all layouts will go inside the main layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    // layout for disabled header
    ModularLayout* header = new ModularLayout();
    header->addWidget(_backButton);
    header->addStretch();
    header->GetLayoutWidget()->setStyleSheet("QWidget {background: #011502;}");

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

    // set the layouts of the respective layout widgets
    header->GetLayoutWidget()->setLayout(header);
    inputLayout->GetLayoutWidget()->setLayout(inputLayout);
    buttonLayout->GetLayoutWidget()->setLayout(buttonLayout);

    // create a group box for the input and create project button
    QVBoxLayout* inputBoxLayout = new QVBoxLayout();
    inputBoxLayout->addWidget(inputLayout->GetLayoutWidget());
    inputBoxLayout->addWidget(buttonLayout->GetLayoutWidget());

    // create a group box for the user to enter the project name in
    QGroupBox* inputBox = new QGroupBox();
    inputBox->setLayout(inputBoxLayout);

    // add the widgets to the main layout and show it
    mainLayout->addWidget(header->GetLayoutWidget());
    mainLayout->addStretch();
    mainLayout->addWidget(inputBox);
    mainLayout->addStretch();

    this->setLayout(mainLayout);
}

void CreateProjectScene::Retranslate()
{
    // translate the strings into a specified language
    _backButton->setToolTip(tr("Go Back"));
    _nameLabel->setText(tr("Project Name: "));
    _createProject->setText(tr("Create Project"));
    _createProject->setToolTip(tr("Create Project"));
}

void CreateProjectScene::UpdateScene()
{

}

void CreateProjectScene::MakeConnections()
{
    // if the create project button is pressed, create the project and show the edit scene or projects scene
    connect(_createProject, SIGNAL(clicked()), this, SLOT(CreateProject()));
    // if the back button is pressed show the projects scene
    connect(_backButton, SIGNAL(clicked()), this, SLOT(GoBack()));
}

void CreateProjectScene::CreateProject()
{
    // create a project with the name the user entered
    Project* project = _projectManager.CreateProject(_nameInput->text());

    // set the current project and show next scene
    if(project != NULL)
    {
        _projectManager.SetCurrentProject(project);
        _sceneManager.SetScene("edit");
        return;
    }

    _sceneManager.SetScene("projects");
}

void CreateProjectScene::GoBack()
{
    // return to the projects screen
    _sceneManager.SetScene("projects");
}
