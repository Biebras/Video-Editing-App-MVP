#ifndef PROJECTSSCENE_H
#define PROJECTSSCENE_H

#include "scene.h"
#include <QtWidgets>
#include "scenemanager.h"
#include "projectmanager.h"

class ProjectsScene : public Scene
{
    Q_OBJECT

    public:
        ProjectsScene(QString sceneName) : Scene(sceneName)
        {
            CreateWidgets();
            ArrangeWidgets();
            MakeConnections();
        };

        void UpdateScene() override;

    private:
        void CreateWidgets() override;
        void ArrangeWidgets() override;
        void MakeConnections() override;
        SceneManager& _sceneManager = SceneManager::Get();
        ProjectManager& _projectManager = ProjectManager::Get();
        QVBoxLayout* _mainLayout = new QVBoxLayout();
        QVBoxLayout* _projectsLayout = new QVBoxLayout();
        QLabel* _title;
        QPushButton* _addProject;
        QList<QPushButton*> _projectButtons;
        // no way of finding previous projects, so leave displaying those for now

    public slots:
        void ChangeSceneToCreateProject();
};

#endif // PROJECTSSCENE_H
