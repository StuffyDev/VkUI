#pragma once

#include "parser/StyledNode.hpp"
#include "LayoutBox.hpp"
#include <memory>

class LayoutEngine {
public:
    static std::unique_ptr<LayoutBox> buildLayoutTree(const StyledNode& styledRoot);

private:
    void layout(LayoutBox& box, const Rect& containingBlock);
    
    // Member variables for the layout process
    Rect m_containingBlock;
};
