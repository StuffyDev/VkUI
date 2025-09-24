#pragma once
#include <string>
#include <map>
#include "Logger.hpp"
struct Color { float r, g, b, a; };
inline Color parseColor(const std::string& colorStr) {
    static const std::map<std::string, Color> colorMap = {
        {"black", {0.0f, 0.0f, 0.0f, 1.0f}}, {"white", {1.0f, 1.0f, 1.0f, 1.0f}},
        {"gray",  {0.5f, 0.5f, 0.5f, 1.0f}}
    };
    auto it = colorMap.find(colorStr);
    if (it != colorMap.end()) return it->second;
    Log::warn("Unknown color: " + colorStr);
    return {1.0f, 0.0f, 1.0f, 1.0f};
}
