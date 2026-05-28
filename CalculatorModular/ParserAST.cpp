#include "ParserAST.hpp"
//#include "ASTNode.hpp"
#include "NumberNode.hpp"
#include "BinaryOpNode.hpp"
#include <stdexcept>
#include <cmath>

Parser::Parser(Tokenizer tokenizer)
    : m_tokenizer(tokenizer),
      m_currentToken(m_tokenizer.getNextToken())
{
}

void Parser::eat(TokenType type)
{
    if (m_currentToken.type == type)
    {
        m_currentToken = m_tokenizer.getNextToken();
    }
    else
    {
        throw std::runtime_error("Unexpected token");
    }
}

double Parser::parse()
{
    auto tree = parseExpression();

    if (m_currentToken.type != TokenType::End)
    {
        throw std::runtime_error("Invalid syntax");
    }

    return tree->evaluate();
}




std::unique_ptr<ASTNode> Parser::parseExpression()
{
    auto left = parseTerm();

    while (
        m_currentToken.type == TokenType::Plus ||
        m_currentToken.type == TokenType::Minus)
    {
        TokenType op = m_currentToken.type;

        eat(op);

        auto right = parseTerm();

        left = std::make_unique<BinaryOpNode>(
            op,
            std::move(left),
            std::move(right));
    }

    return left;
}


std::unique_ptr<ASTNode> Parser::parseTerm()
{
    auto left = parsePower();

    while (
        m_currentToken.type == TokenType::Multiply ||
        m_currentToken.type == TokenType::Divide ||
        m_currentToken.type == TokenType::Module)
    {
        TokenType op = m_currentToken.type;

        eat(op);

        auto right = parsePower();

        left = std::make_unique<BinaryOpNode>(
            op,
            std::move(left),
            std::move(right));
    }

    return left;
}



std::unique_ptr<ASTNode> Parser::parsePower()
{
    auto left = parseFactor();

    if(m_currentToken.type == TokenType::Power)
    {
        TokenType op = m_currentToken.type;

        eat(TokenType::Power);

        auto right = parsePower();

        left = std::make_unique<BinaryOpNode>(
            op,
            std::move(left),
            std::move(right));
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::parseFactor()
{
    if (m_currentToken.type == TokenType::Number)
    {
        double value = m_currentToken.value;

        eat(TokenType::Number);

        return std::make_unique<NumberNode>(value);
    }

    if (m_currentToken.type == TokenType::LeftParen)
    {
        eat(TokenType::LeftParen);

        auto node = parseExpression();

        eat(TokenType::RightParen);

        return node;
    }

    throw std::runtime_error("Expected number or '('");
}

