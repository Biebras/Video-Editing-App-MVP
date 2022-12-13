#include "modularlayout.h"

ModularLayout::~ModularLayout()
{
    delete(_layoutWidget);
    _layoutWidget = NULL;
}

QWidget* ModularLayout::GetLayoutWidget()
{
    return _layoutWidget;
}

void ModularLayout::ClearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            ClearLayout(childLayout, deleteWidgets);
        delete item;
    }
}
