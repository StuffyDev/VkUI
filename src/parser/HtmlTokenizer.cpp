#include "parser/HtmlTokenizer.hpp"
#include <cctype> // for isspace

HtmlTokenizer::HtmlTokenizer(const std::string& source) : m_source(source) {}

std::vector<Token> HtmlTokenizer::tokenize() {
    std::vector<Token> tokens;
    while (!eof()) {
        tokens.push_back(nextToken());
    }
    tokens.push_back({TokenType::END_OF_FILE, ""});
    return tokens;
}

Token HtmlTokenizer::nextToken() {
    consumeWhitespace();
    if (eof()) return {TokenType::END_OF_FILE, ""};

    if (peekChar() == '<') {
        consumeChar(); // Consume '<'
        if (peekChar() == '/') {
            consumeChar(); // Consume '/'
            std::string tagName = consumeWhile([](char c){ return c != '>'; });
            consumeChar(); // Consume '>'
            return {TokenType::CLOSE_TAG, tagName};
        } else {
            std::string tagName = consumeWhile([](char c){ return c != '>'; });
            consumeChar(); // Consume '>'
            return {TokenType::OPEN_TAG, tagName};
        }
    } else {
        std::string text = consumeWhile([](char c){ return c != '<'; });
        return {TokenType::TEXT, text};
    }
}

char HtmlTokenizer::consumeChar() {
    return m_source[m_pos++];
}

char HtmlTokenizer::peekChar() const {
    if (eof()) return '\0';
    return m_source[m_pos];
}

bool HtmlTokenizer::eof() const {
    return m_pos >= m_source.length();
}

void HtmlTokenizer::consumeWhitespace() {
    while (!eof() && isspace(peekChar())) {
        consumeChar();
    }
}

std::string HtmlTokenizer::consumeWhile(std::function<bool(char)> predicate) {
    std::string result;
    while (!eof() && predicate(peekChar())) {
        result += consumeChar();
    }
    return result;
}
