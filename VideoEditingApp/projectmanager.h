#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QList>
#include "project.h"

class ProjectManager
{
    public:
        ProjectManager(const ProjectManager&) = delete;

        static ProjectManager& Get()
        {
            static ProjectManager instance;
            return instance;
        };

        void LoadProjects(QString projectsFolderPath);
        ~ProjectManager();
        void AddProject(Project* project);
        void RemoveProject(Project* project);
        void SetCurrentProject(Project* project);
        int GetTotalProjects();
        Project* GetCurrentProject();
        Project* GetProject(int index);
        Project* GetProjectByName(QString projectName);

    private:
        ProjectManager(){}
        QList<Project*> _projects;
        Project* _currentProject;
};

#endif // PROJECTMANAGER_H
