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
