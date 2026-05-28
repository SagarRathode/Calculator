#ifndef _PARSERAST_HPP
#define _PARSERAST_HPP

#include "Tokenizer.hpp"
#include "ASTNode.hpp"

#include <memory>

class Parser
{
private:

    Tokenizer m_tokenizer;
    Token m_currentToken;

    void eat(TokenType type);

    std::unique_ptr<ASTNode> parseExpression();
    std::unique_ptr<ASTNode> parseTerm();
    std::unique_ptr<ASTNode> parseFactor();
    std::unique_ptr<ASTNode> parsePower();

public:

    Parser(Tokenizer tokenizer);

    double parse();
};

#endif