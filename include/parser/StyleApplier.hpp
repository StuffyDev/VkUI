#pragma once

#include "DomNode.hpp"
#include "StyledNode.hpp"
#include "CssStructs.hpp"
#include <memory>

class StyleApplier {
public:
    static std::unique_ptr<StyledNode> applyStyles(const DomNode& root, const Stylesheet& stylesheet);

private:
    static bool matches(const DomNode& node, const Selector& selector);
};
