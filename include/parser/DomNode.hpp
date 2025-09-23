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

    // Children of this node
    std::vector<std::unique_ptr<DomNode>> children;
    
    // Type of the node (element or text)
    NodeType type;

    // For an element node, this is the tag name. For a text node, the content.
    std::string value;

    // TODO: Add attributes map
    // std::map<std::string, std::string> attributes;
};
