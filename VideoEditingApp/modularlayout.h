#ifndef MODULARLAYOUT_H
#define MODULARLAYOUT_H

#include <QWidget>
#include <QHBoxLayout>

class ModularLayout : public QHBoxLayout
{
    public:
        ModularLayout()  : QHBoxLayout()
        {
            // set a layout widget for the layout automatically
            _layoutWidget = new QWidget();
            _layoutWidget->setLayout(this);
        };

        ~ModularLayout();
        QWidget* GetLayoutWidget();

    private:
        QWidget* _layoutWidget;
};

#endif // MODULARLAYOUT_H
