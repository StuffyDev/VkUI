#pragma once

#include "CssStructs.hpp"
#include <string>
#include <vector>
#include <functional> // <-- Добавим для std::function

class CssParser {
public:
    CssParser(const std::string& source);
    Stylesheet parse();

private:
    void consumeWhitespace();
    char peekChar() const;
    char consumeChar();
    bool eof() const;

    // Вспомогательная функция, которую я забыл объявить
    std::string consumeWhile(std::function<bool(char)> predicate);

    std::string parseIdentifier();
    Selector parseSelector();
    std::vector<Selector> parseSelectors();
    Declaration parseDeclaration();
    std::vector<Declaration> parseDeclarations();
    CssRule parseRule();
    std::string parseValue();

    // Переменные, которые я случайно удалил
    std::string m_source;
    size_t m_pos = 0;
};
