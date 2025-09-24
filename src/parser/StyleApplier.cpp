#include "parser/StyleApplier.hpp"
#include <sstream>
#include <algorithm>

// Вспомогательная функция для разделения строки классов "class1 class2" на вектор
std::vector<std::string> splitClasses(const std::string& classString) {
    std::vector<std::string> classes;
    std::stringstream ss(classString);
    std::string item;
    while (std::getline(ss, item, ' ')) {
        if (!item.empty()) {
            classes.push_back(item);
        }
    }
    return classes;
}


bool StyleApplier::matches(const DomNode& node, const Selector& selector) {
    if (node.type != NodeType::ELEMENT_NODE) return false;

    // Проверка имени тега (или универсального селектора '*')
    if (selector.tagName != "*" && node.value != selector.tagName) {
        return false;
    }

    // Проверка классов
    if (!selector.classes.empty()) {
        auto it = node.attributes.find("class");
        if (it == node.attributes.end()) return false; // У узла нет атрибута class

        std::vector<std::string> nodeClasses = splitClasses(it->second);
        for (const auto& requiredClass : selector.classes) {
            if (std::find(nodeClasses.begin(), nodeClasses.end(), requiredClass) == nodeClasses.end()) {
                return false; // Не найден один из требуемых классов
            }
        }
    }

    return true;
}

std::unique_ptr<StyledNode> StyleApplier::applyStyles(const DomNode& root, const Stylesheet& stylesheet) {
    auto styledNode = std::make_unique<StyledNode>(root);

    for (const auto& rule : stylesheet.rules) {
        for (const auto& selector : rule.selectors) {
            if (matches(root, selector)) {
                for (const auto& declaration : rule.declarations) {
                    styledNode->specifiedValues[declaration.first] = declaration.second;
                }
            }
        }
    }

    for (const auto& child : root.children) {
        styledNode->children.push_back(applyStyles(*child, stylesheet));
    }

    return styledNode;
}
