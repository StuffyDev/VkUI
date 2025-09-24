#pragma once

#include <string>
#include <cstdint>

struct Color {
    uint8_t r = 0, g = 0, b = 0, a = 255;
};

// Parses a hex color string like "#RRGGBB"
inline Color parseHexColor(const std::string& hex) {
    Color color;
    if (hex.length() == 7 && hex[0] == '#') {
        color.r = std::stoi(hex.substr(1, 2), nullptr, 16);
        color.g = std::stoi(hex.substr(3, 2), nullptr, 16);
        color.b = std::stoi(hex.substr(5, 2), nullptr, 16);
    }
    return color;
}
