#pragma once

#include "Token.hpp"
#include <string>
#include <vector>
#include <functional> // <-- The missing include

class HtmlTokenizer {
public:
    HtmlTokenizer(const std::string& source);
    
    std::vector<Token> tokenize();

private:
    Token nextToken();
    char consumeChar();
    char peekChar() const;
    bool eof() const;
    void consumeWhitespace();

    std::string consumeWhile(std::function<bool(char)> predicate);

    std::string m_source;
    size_t m_pos = 0;
};
