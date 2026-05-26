#include "Parser.hpp"

#include <stdexcept>

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
    double result = parseExpression();

    if (m_currentToken.type != TokenType::End)
    {
        throw std::runtime_error("Invalid syntax");
    }

    return result;
}

double Parser::parseExpression()
{
    double result = parseTerm();

    while (
        m_currentToken.type == TokenType::Plus ||
        m_currentToken.type == TokenType::Minus)
    {
        TokenType op = m_currentToken.type;

        eat(op);

        if (op == TokenType::Plus)
        {
            result += parseTerm();
        }
        else
        {
            result -= parseTerm();
        }
    }

    return result;
}

double Parser::parseTerm()
{
    double result = parseFactor();

    while (
        m_currentToken.type == TokenType::Multiply ||
        m_currentToken.type == TokenType::Divide)
    {
        TokenType op = m_currentToken.type;

        eat(op);

        double rhs = parseFactor();

        if (op == TokenType::Multiply)
        {
            result *= rhs;
        }
        else
        {
            if (rhs == 0.0)
            {
                throw std::runtime_error("Division by zero");
            }

            result /= rhs;
        }
    }

    return result;
}

double Parser::parseFactor()
{
    if (m_currentToken.type == TokenType::Number)
    {
        double value = m_currentToken.value;

        eat(TokenType::Number);

        return value;
    }

    if (m_currentToken.type == TokenType::LeftParen)
    {
        eat(TokenType::LeftParen);

        double result = parseExpression();

        eat(TokenType::RightParen);

        return result;
    }

    throw std::runtime_error("Expected number or '('");
}