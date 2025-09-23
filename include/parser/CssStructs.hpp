#pragma once

#include <string>
#include <vector>
#include <map>

// Represents a single "property: value;" declaration
using Declaration = std::pair<std::string, std::string>;

// Represents a selector. For now, we only support simple tag names.
struct Selector {
    std::string tagName;
    // TODO: Add id, classes, etc.
};

// Represents a full CSS rule: "selector { declarations }"
struct CssRule {
    std::vector<Selector> selectors;
    std::vector<Declaration> declarations;
};

// Represents a full stylesheet with multiple rules.
struct Stylesheet {
    std::vector<CssRule> rules;
};
