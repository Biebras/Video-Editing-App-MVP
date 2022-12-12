#include <QDir>
#include <QString>
#include <QDebug>
#include "projectmanager.h"

void ProjectManager::LoadProjects(string projectsFolderPath)
{
    //Create access to directory's contet
    QDir dir (QString::fromStdString(projectsFolderPath));
    //Ignore dot and dot dot
    QFileInfoList fList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::DirsFirst);

    for(int i=0;i < fList.size(); ++i)
    {
        QFileInfo file = fList.at(i);

        Project* project = new Project( file.absoluteFilePath().toStdString(), file.fileName().toStdString());
        AddProject(project);
    }

    if(_projects.count() == 0)
    {
        qDebug() << "No projects found, there's something wrong with projects path name ";
    }
}

ProjectManager::~ProjectManager()
{
    qDeleteAll(_projects);
    _projects.clear();
}

void ProjectManager::AddProject(Project *project)
{
        _projects.append(project);
}

void ProjectManager::RemoveProject(Project *project)
{
    bool success = _projects.removeOne(project);

    if(!success)
        qDebug() << "Couldn't remove video";
}

void ProjectManager::SetCurrentProject(Project *project)
{
     project->LoadProjectVideos();
    _currentProject = project;
}

Project* ProjectManager::GetCurrentProject()
{
    return _currentProject;
}

Project* ProjectManager::GetProject(int index)
{
    if (index < GetTotalProjects() && index > -1)
        return _projects[index];

    qDebug() <<  "Couldn't retrieve video at index: " << index;
    return NULL;
}

Project* ProjectManager::GetProjectByName(string projectName)
{
    for(int i = 0; i < GetTotalProjects(); i++)
    {
        Project* project = GetProject(i);

        if(project->GetProjectName().compare(projectName) == 0)
            return project;
    }

    qDebug() << "Couldn't find project with name" << QString::fromStdString(projectName);
    return NULL;
}

int ProjectManager::GetTotalProjects()
{
    return _projects.size();
}
