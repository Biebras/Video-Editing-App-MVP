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

void CreateProjectScene::Retranslate()
{
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
    connect(_createProject, SIGNAL(clicked()), this, SLOT(CreateProject()));

    connect(_backButton, SIGNAL(clicked()), this, SLOT(GoBack()));
}

void CreateProjectScene::CreateProject()
{
    Project* project = _projectManager.CreateProject(_nameInput->text());

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
    _sceneManager.SetScene("projects");
}
