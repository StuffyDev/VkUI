#pragma once

#include "parser/StyledNode.hpp"
#include <vector>
#include <memory>

// A simple structure for a rectangle
struct Rect {
    float x, y, width, height;
};

// Represents the display type of a box (block or inline)
enum class DisplayType {
    BLOCK,
    INLINE,
    NONE
};

class LayoutBox {
public:
    LayoutBox(const StyledNode& node) : styledNode(node) {}

    const StyledNode& styledNode;
    Rect dimensions;
    DisplayType displayType = DisplayType::BLOCK; // Default to block
    std::vector<std::unique_ptr<LayoutBox>> children;
};
