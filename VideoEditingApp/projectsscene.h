#ifndef PROJECTSSCENE_H
#define PROJECTSSCENE_H

#include "scene.h"
#include <QtWidgets>
#include "scenemanager.h"

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

    private:
        void CreateWidgets() override;
        void ArrangeWidgets() override;
        void MakeConnections() override;
        SceneManager& _sceneManager = SceneManager::Get();
        QLabel* _title;
        QPushButton* _addProject;
        QPushButton* _projectButton;
        // no way of finding previous projects, so leave displaying those for now

    public slots:
        void ChangeSceneToCreateProject();
};

#endif // PROJECTSSCENE_H
