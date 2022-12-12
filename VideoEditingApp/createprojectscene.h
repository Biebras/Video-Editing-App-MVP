#ifndef CREATEPROJECTSCENE_H
#define CREATEPROJECTSCENE_H

#include "scene.h"
#include <QtWidgets>

class CreateProjectScene : public Scene
{
    public:
        CreateProjectScene(): Scene()
        {
            CreateWidgets();
            ArrangeWidgets();
            MakeConnections();
        };

    private:
        void CreateWidgets();
        void ArrangeWidgets();
        void MakeConnections();
        QLabel* _title;
        QPushButton *_addProject;
        QLabel* _nameLabel;
        QLineEdit* _nameInput;
        QPushButton* _createProject;
};

#endif // CREATEPROJECTSCENE_H
