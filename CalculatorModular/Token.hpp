
#ifndef _Token_HPP
#define _Token_HPP
#include <string>

enum class TokenType
{
    Number,
    Plus,
    Minus,
    Multiply,
    Divide,
    LeftParen,
    RightParen,
    End
};

struct Token
{
    TokenType type;
    double value = 0.0;

    Token(TokenType t, double v = 0.0)
        : type(t), value(v)
    {
    }
};
#endif //HPP