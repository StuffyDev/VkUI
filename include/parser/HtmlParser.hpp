#pragma once

#include "Token.hpp"
#include "DomNode.hpp"
#include <vector>
#include <memory>

class HtmlParser {
public:
    HtmlParser(const std::vector<Token>& tokens);

    std::unique_ptr<DomNode> parse();

private:
    std::unique_ptr<DomNode> parseNode();
    std::vector<std::unique_ptr<DomNode>> parseNodes();

    const Token& currentToken() const;
    void consumeToken();
    bool eof() const;

    const std::vector<Token>& m_tokens;
    size_t m_pos = 0;
};
