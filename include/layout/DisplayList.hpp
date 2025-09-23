#pragma once

#include "LayoutBox.hpp"
#include <vector>

// For now, our only command is to draw a solid rectangle
struct SolidRectCommand {
    Rect rect;
    // TODO: Add color
};

using DisplayList = std::vector<SolidRectCommand>;

DisplayList buildDisplayList(const LayoutBox& layoutRoot);
