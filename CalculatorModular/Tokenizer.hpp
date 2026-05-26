
#ifndef _Tokenizer_HPP
#define _Tokenizer_HPP
#include "Token.hpp"
#include <string>

class Tokenizer
{
public:
    explicit Tokenizer(const std::string& input);

    Token getNextToken();

private:
    char currentChar() const;
    void skipWhitespace();
    double parseNumber();

private:
    std::string m_input;
    std::size_t m_position;
};
#endif //HPP