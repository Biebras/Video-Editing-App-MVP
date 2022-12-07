#ifndef SCENE_H
#define SCENE_H

#include <QWidget>

class Scene : public QWidget
{
    Q_OBJECT

    public:
        Scene() : QWidget()
        {
            CreateWidgets();
            ArrangeWidgets();
            MakeConnections();
        };

    private:
        void CreateWidgets();
        void ArrangeWidgets();
        void MakeConnections();
        bool _showScene;

};

#endif // SCENE_H
