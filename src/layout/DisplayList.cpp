#include "layout/DisplayList.hpp"

void buildListRecursive(DisplayList& list, const LayoutBox& layoutBox) {
    if (layoutBox.styledNode.domNode.type == NodeType::ELEMENT_NODE) {
        // For now, just add every element node as a rectangle.
        // Later we'll check CSS properties like `display: none` or `background-color`.
        list.push_back({layoutBox.dimensions});
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
