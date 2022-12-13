#ifndef PROJECTSSCENE_H
#define PROJECTSSCENE_H

#include "scene.h"
#include <QtWidgets>

class ProjectsScene : public Scene
{
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
        QLabel* _title;
        QPushButton *_addProject;
        // no way of finding previous projects, so leave displaying those for now
};

#endif // PROJECTSSCENE_H
