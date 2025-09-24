#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

enum class NodeType {
    ELEMENT_NODE,
    TEXT_NODE
};

class DomNode {
public:
    DomNode(NodeType type, const std::string& value = "") 
        : type(type), value(value) {}

    std::vector<std::unique_ptr<DomNode>> children;
    NodeType type;
    std::string value;

    // Атрибуты элемента, например: class="main"
    std::map<std::string, std::string> attributes;
};
