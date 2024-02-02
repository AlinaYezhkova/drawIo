#pragma once

#include <vector>
#include "ShapeBase.h"

struct Document
{
    QSize                   m_size = {600, 800}; // grid size
    QPoint                  m_offset = {0, 0}; // смещение - меняется при перетягивании холста
    double                  m_scale = 1.0;
    std::vector<ShapeBase*> m_shapes;
    // TODO: MAKE THIS AS LIST to enable moving groups of items
    ShapeBase*              m_selectedShape = nullptr;
};
