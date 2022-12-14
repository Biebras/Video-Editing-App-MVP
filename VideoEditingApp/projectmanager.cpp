#include <QDir>
#include <QString>
#include <QDebug>
#include "projectmanager.h"

void ProjectManager::LoadProjects(QString projectsFolderPath)
{
    //Create access to directory's contet
    QDir projectsDir (projectsFolderPath);
    //create project folder if does not exist
    projectsDir.mkdir("Projects");

    _projectsFolderPath = projectsFolderPath + "/Projects";
    QDir dir(_projectsFolderPath);

    //Ignore dot and dot dot
    QFileInfoList fList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::DirsFirst);

    for(int i=0;i < fList.size(); ++i)
    {
        QFileInfo file = fList.at(i);

        Project* project = new Project( file.absoluteFilePath(), file.fileName());
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

void ProjectManager::CreateProject(QString projectName)
{
    QDir dir(_projectsFolderPath);
    dir.mkdir(projectName);

    Project* project = new Project(_projectsFolderPath + "/" + projectName, projectName);
    AddProject(project);
}

void ProjectManager::AddProject(Project *project)
{
        _projects.push_back(project);
}

void ProjectManager::RemoveProject(Project *project)
{
    bool success = _projects.removeOne(project);

    if(!success)
        qDebug() << "Couldn't remove video";
}

QString ProjectManager::GetProjectsPath()
{
    return _projectsFolderPath;
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

QList<Project*> ProjectManager::GetProjects()
{
        return _projects;
}

Project* ProjectManager::GetProjectByName(QString projectName)
{
    for(int i = 0; i < GetTotalProjects(); i++)
    {
        Project* project = GetProject(i);

        if(project->GetProjectName().compare(projectName) == 0)
            return project;
    }

    qDebug() << "Couldn't find project with name" << projectName;
    return NULL;
}

int ProjectManager::GetTotalProjects()
{
    return _projects.size();
}

void ProjectManager::PrintProjects()
{
    qDebug() << "Printing projects";
    qDebug() << "==========================================";

    foreach(auto project, _projects)
    {
        qDebug() << "Name: " << project->GetProjectName();
        qDebug() << "Path: " << project->GetProjectPath();
        qDebug() << "==========================================";
    }
}
