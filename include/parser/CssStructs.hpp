#pragma once

#include <string>
#include <vector>
#include <map>

using Declaration = std::pair<std::string, std::string>;

struct Selector {
    std::string tagName;
    std::vector<std::string> classes;
};

struct CssRule {
    std::vector<Selector> selectors;
    std::vector<Declaration> declarations;
};

struct Stylesheet {
    std::vector<CssRule> rules;
};
