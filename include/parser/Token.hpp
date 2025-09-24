#pragma once

#include <string>
#include <vector>
#include <map> // <-- Добавили

enum class TokenType {
    OPEN_TAG,
    CLOSE_TAG,
    TEXT,
    COMMENT,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string value;
    std::map<std::string, std::string> attributes; // <-- Добавили контейнер для атрибутов
};
