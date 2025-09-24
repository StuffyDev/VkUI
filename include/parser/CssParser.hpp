#pragma once

#include "CssStructs.hpp"
#include <string>
#include <vector>
#include <functional> 

class CssParser {
public:
    CssParser(const std::string& source);
    Stylesheet parse();

private:
    void consumeWhitespace();
    char peekChar() const;
    char consumeChar();
    bool eof() const;

    std::string consumeWhile(std::function<bool(char)> predicate);

    std::string parseIdentifier();
    Selector parseSelector();
    std::vector<Selector> parseSelectors();
    Declaration parseDeclaration();
    std::vector<Declaration> parseDeclarations();
    CssRule parseRule();
    std::string parseValue();


    std::string m_source;
    size_t m_pos = 0;
};
