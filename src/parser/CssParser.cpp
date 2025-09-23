#include "parser/CssParser.hpp"
#include <cctype>
#include <stdexcept>

CssParser::CssParser(const std::string& source) : m_source(source) {}

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
    consumeWhitespace();
    rule.declarations = parseDeclarations();
    consumeWhitespace();
    if (consumeChar() != '}') throw std::runtime_error("Expected '}' in CSS rule");
    return rule;
}

std::vector<Declaration> CssParser::parseDeclarations() {
    std::vector<Declaration> declarations;
    while (peekChar() != '}') {
        declarations.push_back(parseDeclaration());
        consumeWhitespace();
    }
    return declarations;
}

Declaration CssParser::parseDeclaration() {
    std::string property = parseIdentifier();
    consumeWhitespace();
    if (consumeChar() != ':') throw std::runtime_error("Expected ':' in CSS declaration");
    consumeWhitespace();
    std::string value = parseIdentifier(); // For now, values are simple identifiers too
    consumeWhitespace();
    if (consumeChar() != ';') throw std::runtime_error("Expected ';' in CSS declaration");
    return {property, value};
}


std::vector<Selector> CssParser::parseSelectors() {
    std::vector<Selector> selectors;
    while (peekChar() != '{') {
        selectors.push_back(parseSelector());
        consumeWhitespace();
        if (peekChar() == ',') {
            consumeChar(); // Consume comma for multiple selectors
            consumeWhitespace();
        }
    }
    return selectors;
}

Selector CssParser::parseSelector() {
    // Super simple: only supports tag names for now.
    Selector selector;
    selector.tagName = parseIdentifier();
    return selector;
}

std::string CssParser::parseIdentifier() {
    std::string result;
    while (!eof() && (isalnum(peekChar()) || peekChar() == '-')) {
        result += consumeChar();
    }
    return result;
}

// --- Helper functions ---
void CssParser::consumeWhitespace() {
    while (!eof() && isspace(peekChar())) { consumeChar(); }
}
char CssParser::peekChar() const {
    return m_pos < m_source.length() ? m_source[m_pos] : '\0';
}
char CssParser::consumeChar() {
    return m_source[m_pos++];
}
bool CssParser::eof() const {
    return m_pos >= m_source.length();
}
