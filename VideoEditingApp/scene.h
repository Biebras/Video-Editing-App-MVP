#ifndef SCENE_H
#define SCENE_H

#include <QWidget>


class Scene : public QWidget
{
    public:
    Scene() : QWidget() {};
        void CreateWidgets();
        void ArrangeWidgets();
        void MakeConnections();

    private:
        bool _showScene;

};

#endif // SCENE_H
