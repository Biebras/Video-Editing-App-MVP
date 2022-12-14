#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QDebug>

class Scene : public QWidget
{
    Q_OBJECT

    public:
        Scene(QString sceneName) : QWidget()
        {
            _sceneName = sceneName;
        };

        QString GetSceneName()
        {
            return _sceneName;
        }

    private:
        virtual void CreateWidgets();
        virtual void ArrangeWidgets();
        virtual void MakeConnections();
        QString _sceneName;

};

#endif // SCENE_H
