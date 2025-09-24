#pragma once

#include "LayoutBox.hpp"
#include "../utils/Color.hpp" // <-- Подключаем нашу утилиту
#include <vector>

// Команда на отрисовку теперь содержит и цвет
struct SolidRectCommand {
    Rect rect;
    Color color;
};

using DisplayList = std::vector<SolidRectCommand>;

DisplayList buildDisplayList(const LayoutBox& layoutRoot);
