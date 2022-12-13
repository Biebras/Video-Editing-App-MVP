#ifndef CREATEPROJECTSCENE_H
#define CREATEPROJECTSCENE_H

#include "scene.h"
#include <QtWidgets>

class CreateProjectScene : public Scene
{
    public:
        CreateProjectScene(QString sceneName) : Scene(sceneName)
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
        QLabel* _nameLabel;
        QLineEdit* _nameInput;
        QPushButton* _createProject;
};

#endif // CREATEPROJECTSCENE_H
