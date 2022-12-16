#include "modularlayout.h"

ModularLayout::~ModularLayout()
{
    // delete the layout widget
    delete(_layoutWidget);
    _layoutWidget = NULL;
}

QWidget* ModularLayout::GetLayoutWidget()
{
    return _layoutWidget;
}
