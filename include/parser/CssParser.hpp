#pragma once

#include "CssStructs.hpp"
#include <string>

class CssParser {
public:
    CssParser(const std::string& source);
    Stylesheet parse();

private:
    void consumeWhitespace();
    char peekChar() const;
    char consumeChar();
    bool eof() const;

    std::string parseIdentifier();
    Selector parseSelector();
    std::vector<Selector> parseSelectors();
    Declaration parseDeclaration();
    std::vector<Declaration> parseDeclarations();
    CssRule parseRule();

    std::string m_source;
    size_t m_pos = 0;
};
