#ifndef MODULARLAYOUT_H
#define MODULARLAYOUT_H

#include <QWidget>
#include <QHBoxLayout>

class ModularLayout : public QHBoxLayout
{
    public:
        ModularLayout()  : QHBoxLayout()
        {
            _layoutWidget = new QWidget();
            _layoutWidget->setLayout(this);
        };

        ~ModularLayout();
        QWidget* GetLayoutWidget();
        void ClearLayout(QLayout* layout, bool deleteWidgets = true);

    private:
        QWidget* _layoutWidget;
};

#endif // MODULARLAYOUT_H
