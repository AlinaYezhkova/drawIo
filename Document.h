#pragma once

#include <vector>
#include "ShapeBase.h"

struct Document
{
    std::vector<ShapeBase*> m_shapes;
};
