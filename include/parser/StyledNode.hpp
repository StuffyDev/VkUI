#pragma once

#include "DomNode.hpp"
#include <map>
#include <string>
#include <vector>
#include <memory>

// A map from CSS property name to value.
using PropertyMap = std::map<std::string, std::string>;

class StyledNode {
public:
    StyledNode(const DomNode& node) : domNode(node) {}

    const DomNode& domNode;
    PropertyMap specifiedValues;
    std::vector<std::unique_ptr<StyledNode>> children;
};
