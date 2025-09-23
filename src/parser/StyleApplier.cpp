#include "parser/StyleApplier.hpp"

// Check if a DOM node matches a simple selector.
bool StyleApplier::matches(const DomNode& node, const Selector& selector) {
    if (node.type != NodeType::ELEMENT_NODE) {
        return false;
    }
    // For now, we only match by tag name.
    return node.value == selector.tagName;
}

std::unique_ptr<StyledNode> StyleApplier::applyStyles(const DomNode& root, const Stylesheet& stylesheet) {
    auto styledNode = std::make_unique<StyledNode>(root);

    // Apply matching rules
    for (const auto& rule : stylesheet.rules) {
        for (const auto& selector : rule.selectors) {
            if (matches(root, selector)) {
                for (const auto& declaration : rule.declarations) {
                    styledNode->specifiedValues[declaration.first] = declaration.second;
                }
            }
        }
    }

    // Recursively apply styles to children
    for (const auto& child : root.children) {
        styledNode->children.push_back(applyStyles(*child, stylesheet));
    }

    return styledNode;
}
