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
        void LoadLanguage(const QString& rLanguage);
        void CreateMenuWindow();
        void CreateLanguageMenu(void);

         const int AppLayoutMaxX = 800;

    protected:
        void resizeEvent(QResizeEvent *event) override;
};

#endif // PRIMARYWINDOW_H
