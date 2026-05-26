#include "Tokenizer.hpp"

#include <cctype>
#include <stdexcept>

Tokenizer::Tokenizer(const std::string& input)
    : m_input(input),
      m_position(0)
{
}

char Tokenizer::currentChar() const
{
    if (m_position >= m_input.length())
    {
        return '\0';
    }

    return m_input[m_position];
}

void Tokenizer::skipWhitespace()
{
    while (std::isspace(currentChar()))
    {
        ++m_position;
    }
}

double Tokenizer::parseNumber()
{
    std::string numberString;

    while (std::isdigit(currentChar()) || currentChar() == '.')
    {
        numberString += currentChar();
        ++m_position;
    }

    return std::stod(numberString);
}

Token Tokenizer::getNextToken()
{
    skipWhitespace();

    char ch = currentChar();

    if (ch == '\0')
    {
        return Token(TokenType::End);
    }

    if (std::isdigit(ch) || ch == '.')
    {
        return Token(TokenType::Number, parseNumber());
    }

    ++m_position;

    switch (ch)
    {
        case '+':
            return Token(TokenType::Plus);

        case '-':
            return Token(TokenType::Minus);

        case '*':
            return Token(TokenType::Multiply);

        case '/':
            return Token(TokenType::Divide);

        case '(':
            return Token(TokenType::LeftParen);

        case ')':
            return Token(TokenType::RightParen);

        default:
            throw std::runtime_error("Invalid character");
    }
}