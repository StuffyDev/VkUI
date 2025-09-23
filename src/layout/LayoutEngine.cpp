#include "layout/LayoutEngine.hpp"
#include <string>

// Static entry point
std::unique_ptr<LayoutBox> LayoutEngine::buildLayoutTree(const StyledNode& styledRoot) {
    LayoutEngine engine;
    
    // For now, the root containing block is the whole window.
    // Let's assume a window of 800x600.
    engine.m_containingBlock = {0.0f, 0.0f, 800.0f, 600.0f};

    // Build the tree structure first
    auto layoutRoot = std::make_unique<LayoutBox>(styledRoot);
    for (const auto& child : styledRoot.children) {
        // Skip text nodes that are all whitespace
        if (child->domNode.type == NodeType::TEXT_NODE) {
            size_t first = child->domNode.value.find_first_not_of(" \t\n\r");
            if (std::string::npos == first) continue;
        }
        layoutRoot->children.push_back(buildLayoutTree(*child));
    }

    // Now, calculate the dimensions and positions
    engine.layout(*layoutRoot, engine.m_containingBlock);
    
    return layoutRoot;
}

void LayoutEngine::layout(LayoutBox& box, const Rect& containingBlock) {
    if (box.styledNode.domNode.type == NodeType::ELEMENT_NODE) {
        // --- Calculate dimensions for a block-level element ---

        // The width is the width of the containing block
        box.dimensions.x = containingBlock.x;
        box.dimensions.width = containingBlock.width;

        // The y position is at the bottom of the previous block
        box.dimensions.y = containingBlock.y;
        
        // --- Layout children ---
        float currentY = 0.0f;
        for (auto& child : box.children) {
            // Each child's containing block starts at the current y offset
            Rect childContainingBlock = {0.0f, currentY, box.dimensions.width, 0.0f};
            layout(*child, childContainingBlock);
            // After laying out a child, move the y offset down by its height
            currentY += child->dimensions.height;
        }

        // --- Calculate height ---
        // For now, the height of a block is just the sum of its children's heights.
        // We'll add padding/margin/border later. A box with no children has a fixed height.
        box.dimensions.height = currentY;
        if (box.children.empty()) {
            // Simple placeholder height for elements without children (like <p>)
            box.dimensions.height = 20.0f; // e.g., line height
        }
    }
    // Note: Text nodes currently don't get dimensions. We'll handle them later.
}
