#ifndef MODULARLAYOUT_H
#define MODULARLAYOUT_H

#include <QWidget>
#include <QHBoxLayout>

class ModularLayout : public QHBoxLayout
{
    public:
        ModularLayout()  : QHBoxLayout() {};
        ~ModularLayout();
        QWidget* GetLayoutWidget();

    private:
        QWidget* _layoutWidget;
};

#endif // MODULARLAYOUT_H