#include "parser/HtmlParser.hpp"
#include "Logger.hpp"

HtmlParser::HtmlParser(const std::vector<Token>& tokens) : m_tokens(tokens) {}

std::unique_ptr<DomNode> HtmlParser::parse() {
    auto nodes = parseNodes();
    // For a valid HTML document, there should be one root node (e.g., <html>)
    // For simplicity, we'll just create a dummy "root" if there are multiple top-level nodes.
    if (nodes.size() == 1) {
        return std::move(nodes[0]);
    } else {
        auto root = std::make_unique<DomNode>(NodeType::ELEMENT_NODE, "root");
        root->children = std::move(nodes);
        return root;
    }
}

// Parses a sequence of nodes until a closing tag is found that matches an ancestor.
std::vector<std::unique_ptr<DomNode>> HtmlParser::parseNodes() {
    std::vector<std::unique_ptr<DomNode>> nodes;
    while (!eof()) {
        if (currentToken().type == TokenType::OPEN_TAG) {
            nodes.push_back(parseNode());
        } else if (currentToken().type == TokenType::CLOSE_TAG || currentToken().type == TokenType::END_OF_FILE) {
            // Stop parsing at a closing tag or EOF, let the parent handle it.
            break; 
        } else {
             // Handle text nodes
            nodes.push_back(parseNode());
        }
    }
    return nodes;
}

// Parses a single element or text node.
std::unique_ptr<DomNode> HtmlParser::parseNode() {
    if (currentToken().type == TokenType::TEXT) {
        auto node = std::make_unique<DomNode>(NodeType::TEXT_NODE, currentToken().value);
        consumeToken();
        return node;
    }

    // It must be an element node
    std::string tagName = currentToken().value;
    auto node = std::make_unique<DomNode>(NodeType::ELEMENT_NODE, tagName);
    consumeToken(); // Consume the open tag

    // Recursively parse children until we find the corresponding closing tag
    while (!eof() && (currentToken().type != TokenType::CLOSE_TAG || currentToken().value != tagName)) {
        node->children.push_back(parseNode());
    }

    if (eof()) {
        Log::warn("Parser warning: Unclosed tag '" + tagName + "'");
    } else {
        consumeToken(); // Consume the close tag
    }

    return node;
}


const Token& HtmlParser::currentToken() const {
    return m_tokens[m_pos];
}

void HtmlParser::consumeToken() {
    m_pos++;
}

bool HtmlParser::eof() const {
    return m_pos >= m_tokens.size() || currentToken().type == TokenType::END_OF_FILE;
}
