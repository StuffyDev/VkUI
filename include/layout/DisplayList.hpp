#pragma once

#include "LayoutBox.hpp"
#include "../utils/Color.hpp" 
#include <vector>

struct SolidRectCommand {
    Rect rect;
    Color color;
};

using DisplayList = std::vector<SolidRectCommand>;

DisplayList buildDisplayList(const LayoutBox& layoutRoot);
