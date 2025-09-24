#include "parser/HtmlTokenizer.hpp"
#include <cctype>

HtmlTokenizer::HtmlTokenizer(const std::string& source) : m_source(source) {}

std::vector<Token> HtmlTokenizer::tokenize() {
    std::vector<Token> tokens;
    while (!eof()) {
        tokens.push_back(nextToken());
    }
    tokens.push_back({TokenType::END_OF_FILE, ""});
    return tokens;
}

// Вспомогательные функции для парсинга атрибутов
std::string HtmlTokenizer::parseAttributeValue() {
    consumeWhitespace();
    std::string value;
    if (peekChar() == '"') {
        consumeChar(); // consume opening quote
        value = consumeWhile([](char c){ return c != '"'; });
        consumeChar(); // consume closing quote
    }
    return value;
}

std::map<std::string, std::string> HtmlTokenizer::parseAttributes() {
    std::map<std::string, std::string> attributes;
    while (peekChar() != '>') {
        consumeWhitespace();
        std::string name = consumeWhile([](char c){ return isalnum(c); });
        consumeWhitespace();
        if (peekChar() == '=') {
            consumeChar();
            attributes[name] = parseAttributeValue();
        }
    }
    return attributes;
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
            std::string tagName = consumeWhile([](char c){ return !isspace(c) && c != '>'; });
            auto attributes = parseAttributes();
            consumeChar(); // Consume '>'
            return {TokenType::OPEN_TAG, tagName, attributes};
        }
    } else {
        std::string text = consumeWhile([](char c){ return c != '<'; });
        return {TokenType::TEXT, text};
    }
}

// Остальные вспомогательные функции без изменений
char HtmlTokenizer::consumeChar() { return m_source[m_pos++]; }
char HtmlTokenizer::peekChar() const { return eof() ? '\0' : m_source[m_pos]; }
bool HtmlTokenizer::eof() const { return m_pos >= m_source.length(); }
void HtmlTokenizer::consumeWhitespace() { while (!eof() && isspace(peekChar())) consumeChar(); }
std::string HtmlTokenizer::consumeWhile(std::function<bool(char)> predicate) {
    std::string result;
    while (!eof() && predicate(peekChar())) result += consumeChar();
    return result;
}
