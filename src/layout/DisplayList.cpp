#include "layout/DisplayList.hpp"
#include <iostream>

void buildListRecursive(DisplayList& list, const LayoutBox& layoutBox) {
    if (layoutBox.styledNode.domNode.type == NodeType::ELEMENT_NODE) {
        Color color; // Цвет по умолчанию - черный
        auto it = layoutBox.styledNode.specifiedValues.find("background");
        if (it != layoutBox.styledNode.specifiedValues.end()) {
            // Если нашли свойство background, парсим его
            color = parseHexColor(it->second);
        }
        
        list.push_back({layoutBox.dimensions, color});
    }

    for (const auto& child : layoutBox.children) {
        buildListRecursive(list, *child);
    }
}

DisplayList buildDisplayList(const LayoutBox& layoutRoot) {
    DisplayList list;
    buildListRecursive(list, layoutRoot);
    return list;
}
