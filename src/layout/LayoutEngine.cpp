#include "layout/LayoutEngine.hpp"
#include "parser/StyledNode.hpp"
#include <string>
#include <algorithm>

float get_px_value(const PropertyMap& values, const std::string& name, float fallback) {
    auto it = values.find(name);
    if (it != values.end()) {
        try {
            std::string val_str = it->second;
            size_t px_pos = val_str.find("px");
            if (px_pos != std::string::npos) val_str.erase(px_pos, 2);
            return std::stof(val_str);
        } catch (...) { return fallback; }
    }
    return fallback;
}

static std::unique_ptr<LayoutBox> build_box_tree(const StyledNode& styledRoot) {
    auto box = std::make_unique<LayoutBox>(styledRoot);
    for (const auto& child_node : styledRoot.children) {
        if (child_node->domNode.type == NodeType::TEXT_NODE && 
            child_node->domNode.value.find_first_not_of(" \t\n\r") == std::string::npos) {
            continue;
        }
        box->children.push_back(build_box_tree(*child_node));
    }
    return box;
}

std::unique_ptr<LayoutBox> LayoutEngine::buildLayoutTree(const StyledNode& styledRoot) {
    auto layoutRoot = build_box_tree(styledRoot);
    if (layoutRoot) {
        LayoutEngine engine;
        Rect initialContainingBlock = {0.0f, 0.0f, 800.0f, 600.0f};
        engine.layout(*layoutRoot, initialContainingBlock);
    }
    return layoutRoot;
}

void LayoutEngine::layout(LayoutBox& box, const Rect& containingBlock) {
    if (box.styledNode.domNode.type != NodeType::ELEMENT_NODE) return;
    auto& values = box.styledNode.specifiedValues;

    // Сначала определяем ширину блока. Либо из CSS, либо от родителя.
    float specifiedWidth = get_px_value(values, "width", 0.0f);
    if (specifiedWidth > 0) {
        box.dimensions.width = specifiedWidth;
    } else {
        box.dimensions.width = containingBlock.width;
    }

    // Позиционируем блок
    box.dimensions.x = containingBlock.x + get_px_value(values, "margin-left", 0.0f);
    box.dimensions.y = containingBlock.y + get_px_value(values, "margin-top", 0.0f);

    // Рассчитываем область для контента (с учетом padding)
    float padding = get_px_value(values, "padding", 0.0f);
    float contentX = box.dimensions.x + padding;
    float contentY = box.dimensions.y + padding;
    // Ширина контента - это ширина нашего блока минус паддинги
    float contentWidth = box.dimensions.width - 2 * padding;

    // Компонуем дочерние элементы внутри области контента
    float contentHeight = 0.0f;
    for (auto& child : box.children) {
        Rect childContainingBlock = { contentX, contentY + contentHeight, contentWidth, 0 };
        layout(*child, childContainingBlock);
        contentHeight += get_px_value(child->styledNode.specifiedValues, "margin-top", 0.0f)
                       + child->dimensions.height
                       + get_px_value(child->styledNode.specifiedValues, "margin-bottom", 0.0f);
    }

    // Рассчитываем финальную высоту блока
    float specifiedHeight = get_px_value(values, "height", 0.0f);
    box.dimensions.height = (specifiedHeight > 0) ? specifiedHeight : (contentHeight + 2 * padding);
}
