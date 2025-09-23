#pragma once

#include <string>
#include <vector>

enum class TokenType {
    OPEN_TAG,
    CLOSE_TAG,
    TEXT,
    COMMENT, // We'll just ignore these for now
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string value;
};
