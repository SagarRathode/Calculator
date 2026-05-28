#ifndef _Parser_HPP
#define _Parser_HPP

#include "Tokenizer.hpp"

class Parser
{
public:
    explicit Parser(Tokenizer tokenizer);

    double parse();

private:
    void eat(TokenType type);

    double parseExpression();
    double parseTerm();
    double parseFactor();
    double parsePower();

private:
    Tokenizer m_tokenizer;
    Token m_currentToken;
};
#endif //HPP
