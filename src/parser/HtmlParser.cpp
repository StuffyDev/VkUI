#include "parser/HtmlParser.hpp"
#include "Logger.hpp"

HtmlParser::HtmlParser(const std::vector<Token>& tokens) : m_tokens(tokens) {}

std::unique_ptr<DomNode> HtmlParser::parse() {
    auto nodes = parseNodes();
    if (nodes.size() == 1) {
        return std::move(nodes[0]);
    } else {
        auto root = std::make_unique<DomNode>(NodeType::ELEMENT_NODE, "root");
        root->children = std::move(nodes);
        return root;
    }
}

std::vector<std::unique_ptr<DomNode>> HtmlParser::parseNodes() {
    std::vector<std::unique_ptr<DomNode>> nodes;
    while (!eof()) {
        if (currentToken().type == TokenType::OPEN_TAG) {
            nodes.push_back(parseNode());
        } else if (currentToken().type == TokenType::CLOSE_TAG || currentToken().type == TokenType::END_OF_FILE) {
            break; 
        } else {
            nodes.push_back(parseNode());
        }
    }
    return nodes;
}

std::unique_ptr<DomNode> HtmlParser::parseNode() {
    if (currentToken().type == TokenType::TEXT) {
        auto node = std::make_unique<DomNode>(NodeType::TEXT_NODE, currentToken().value);
        consumeToken();
        return node;
    }

    std::string tagName = currentToken().value;
    auto node = std::make_unique<DomNode>(NodeType::ELEMENT_NODE, tagName);
    node->attributes = currentToken().attributes; // <-- Копируем атрибуты!
    consumeToken();

    while (!eof() && (currentToken().type != TokenType::CLOSE_TAG || currentToken().value != tagName)) {
        node->children.push_back(parseNode());
    }

    if (eof()) {
        Log::warn("Parser warning: Unclosed tag '" + tagName + "'");
    } else {
        consumeToken();
    }

    return node;
}

const Token& HtmlParser::currentToken() const { return m_tokens[m_pos]; }
void HtmlParser::consumeToken() { m_pos++; }
bool HtmlParser::eof() const { return m_pos >= m_tokens.size() || currentToken().type == TokenType::END_OF_FILE; }
