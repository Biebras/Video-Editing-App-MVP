#ifndef CREATEPROJECTSCENE_H
#define CREATEPROJECTSCENE_H

#include "scene.h"
#include <QtWidgets>
#include "scenemanager.h"
#include "projectmanager.h"

class CreateProjectScene : public Scene
{
    Q_OBJECT

    public:
        CreateProjectScene(QString sceneName) : Scene(sceneName)
        {
            //initialise the scene
            CreateWidgets();
            ArrangeWidgets();
            MakeConnections();
        };

        void UpdateScene() override;
        void Retranslate() override;

    private:
        void CreateWidgets() override;
        void ArrangeWidgets() override;
        void MakeConnections() override;
        SceneManager& _sceneManager = SceneManager::Get();
        ProjectManager& _projectManager = ProjectManager::Get();
        QPushButton* _backButton;
        QLabel* _nameLabel;
        QLineEdit* _nameInput;
        QPushButton* _createProject;

    public slots:
        void CreateProject();
        void GoBack();
};

#endif // CREATEPROJECTSCENE_H
