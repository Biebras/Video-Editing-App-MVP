#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QList>
#include "project.h"

class ProjectManager
{
    public:
        ProjectManager(string projectsFolder);
        ~ProjectManager();
        Project* GetProject(int index);
        Project* GetProjectByName(string projectName);

    private:
        QList<Project*> _projects;
};

#endif // PROJECTMANAGER_H
