#include <QDir>
#include <QString>
#include <QDebug>
#include "projectmanager.h"

// Loads projects from Projects directory
void ProjectManager::LoadProjects(QString projectsFolderPath)
{
    //Create access to directory's contet
    QDir projectsDir (projectsFolderPath);
    //create project folder if does not exist
    projectsDir.mkdir("Projects");

    //Set projects directory path
    _projectsFolderPath = projectsFolderPath + "/Projects";
    QDir dir(_projectsFolderPath);

    //Ignore dot and dot dot
    QFileInfoList fList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::DirsFirst);

    //loop through subdirectories and create project
    for(int i=0;i < fList.size(); ++i)
    {
        QFileInfo file = fList.at(i);

        Project* project = new Project( file.absoluteFilePath(), file.fileName());
        AddProject(project);
    }

    //if no projects were found notify
    if(_projects.count() == 0)
    {
        qDebug() << "No projects found, there's something wrong with projects path name ";
    }
}

//Deconstructor
ProjectManager::~ProjectManager()
{
    qDeleteAll(_projects);
    _projects.clear();
}

//Creates new project with spesified name. Returns NULL if project already exist, otherwise returns pointer to project
Project* ProjectManager::CreateProject(QString projectName)
{
    //creates neccassery QDir
    QDir dir(_projectsFolderPath);
    QDir newDir(_projectsFolderPath + "/" + projectName);

    //if project already exist return NULL
    if(newDir.exists() == true)
    {
        qDebug() << "Can't create project with this name already exists";
        return NULL;
    }

    //create project directory
    dir.mkdir(projectName);

    //create new project and return it
    Project* project = new Project(_projectsFolderPath + "/" + projectName, projectName);
    AddProject(project);

    return project;
}

// Adds project to the project list
void ProjectManager::AddProject(Project *project)
{
        _projects.push_back(project);
}

//Removes project from project list
void ProjectManager::RemoveProject(Project *project)
{
    bool success = _projects.removeOne(project);

    if(!success)
        qDebug() << "Couldn't remove video";
}

//Returns projects directory path
QString ProjectManager::GetProjectsPath()
{
    return _projectsFolderPath;
}

// Sets current project and loads current projects videos
void ProjectManager::SetCurrentProject(Project *project)
{
    _currentProject = project;
    _currentProject->LoadProjectVideos();
}

//Returns current project
Project* ProjectManager::GetCurrentProject()
{
    return _currentProject;
}

//Returns project spesified by index, if index invalid returns NULL
Project* ProjectManager::GetProject(int index)
{
    if (index < GetTotalProjects() && index > -1)
        return _projects[index];

    qDebug() <<  "Couldn't retrieve project at index: " << index;
    return NULL;
}

// returns projects list
QList<Project*> ProjectManager::GetProjects()
{
        return _projects;
}

// returns project by spesified name, if project with this name do not exist returns NULL
Project* ProjectManager::GetProjectByName(QString projectName)
{
    //loop through projects, return first that matches
    for(int i = 0; i < GetTotalProjects(); i++)
    {
        Project* project = GetProject(i);

        if(project->GetProjectName().compare(projectName) == 0)
            return project;
    }

    qDebug() << "Couldn't find project with name" << projectName;
    return NULL;
}

// return projects count
int ProjectManager::GetTotalProjects()
{
    return _projects.size();
}

// Prints all loaded projects
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
