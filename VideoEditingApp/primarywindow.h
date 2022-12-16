#ifndef PRIMARYWINDOW_H
#define PRIMARYWINDOW_H

#include <QtWidgets>

class PrimaryWindow : public QMainWindow
{
    Q_OBJECT

    public:
        PrimaryWindow();

        bool IsAppLayout;

    private:
        //from where horizontal mode begins
         const int AppLayoutMaxX = 800;

    protected:
        void resizeEvent(QResizeEvent *event) override;
};

#endif // PRIMARYWINDOW_H
