#include "parser/CssParser.hpp"
#include <cctype>
#include <stdexcept>
#include <algorithm>

CssParser::CssParser(const std::string& source) : m_source(source), m_pos(0) {}

Stylesheet CssParser::parse() {
    Stylesheet sheet;
    while (!eof()) {
        consumeWhitespace();
        if (eof()) break;
        sheet.rules.push_back(parseRule());
    }
    return sheet;
}

CssRule CssParser::parseRule() {
    CssRule rule;
    rule.selectors = parseSelectors();
    consumeWhitespace();
    if (consumeChar() != '{') throw std::runtime_error("Expected '{' in CSS rule");
    rule.declarations = parseDeclarations();
    if (consumeChar() != '}') throw std::runtime_error("Expected '}' in CSS rule");
    return rule;
}

std::vector<Selector> CssParser::parseSelectors() {
    std::vector<Selector> selectors;
    while (peekChar() != '{') {
        selectors.push_back(parseSelector());
        consumeWhitespace();
        if (peekChar() == ',') {
            consumeChar();
            consumeWhitespace();
        }
    }
    return selectors;
}

Selector CssParser::parseSelector() {
    Selector selector;
    std::string raw_selector = consumeWhile([](char c) { return c != '{' && c != ',' && !isspace(c); });
    
    size_t class_pos = raw_selector.find('.');
    if (class_pos != std::string::npos) {
        selector.tagName = raw_selector.substr(0, class_pos);
        if (selector.tagName.empty()) selector.tagName = "*"; // Handle selectors like .class
        selector.classes.push_back(raw_selector.substr(class_pos + 1));
    } else {
        selector.tagName = raw_selector;
    }
    return selector;
}

std::vector<Declaration> CssParser::parseDeclarations() {
    std::vector<Declaration> declarations;
    while (peekChar() != '}') {
        consumeWhitespace();
        if (peekChar() == '}') break; // Выходим, если достигли конца блока
        declarations.push_back(parseDeclaration());
    }
    return declarations;
}

Declaration CssParser::parseDeclaration() {
    std::string property = parseIdentifier();
    consumeWhitespace();
    if (consumeChar() != ':') throw std::runtime_error("Expected ':' in declaration");
    consumeWhitespace();
    std::string value = consumeWhile([](char c) { return c != ';'; });
    // Trim leading/trailing whitespace from value
    value.erase(0, value.find_first_not_of(" \t\n\r"));
    value.erase(value.find_last_not_of(" \t\n\r") + 1);
    
    if (consumeChar() != ';') throw std::runtime_error("Expected ';' after declaration value");
    return {property, value};
}

std::string CssParser::parseIdentifier() {
    return consumeWhile([](char c) { return isalnum(c) || c == '-'; });
}

// --- Вспомогательные функции ---
void CssParser::consumeWhitespace() { while (!eof() && isspace(peekChar())) consumeChar(); }
char CssParser::peekChar() const { return m_pos < m_source.length() ? m_source[m_pos] : '\0'; }
char CssParser::consumeChar() { return m_source[m_pos++]; }
bool CssParser::eof() const { return m_pos >= m_source.length(); }
std::string CssParser::consumeWhile(std::function<bool(char)> predicate) {
    std::string result;
    while (!eof() && predicate(peekChar())) {
        result += consumeChar();
    }
    return result;
}
