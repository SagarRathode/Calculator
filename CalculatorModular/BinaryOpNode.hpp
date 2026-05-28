#ifndef _BINARYOPNODE_HPP
#define _BINARYOPNODE_HPP

#include "ASTNode.hpp"
#include "Token.hpp"

#include <memory>
#include <cmath>
#include <stdexcept>

class BinaryOpNode : public ASTNode
{
private:
    TokenType m_op;

    std::unique_ptr<ASTNode> m_left;
    std::unique_ptr<ASTNode> m_right;

public:
    BinaryOpNode(
        TokenType op,
        std::unique_ptr<ASTNode> left,
        std::unique_ptr<ASTNode> right)
        :
        m_op(op),
        m_left(std::move(left)),
        m_right(std::move(right))
    {
    }

    double evaluate() override
    {
        double lhs = m_left->evaluate();
        double rhs = m_right->evaluate();

        switch(m_op)
        {
            case TokenType::Plus:
                return lhs + rhs;

            case TokenType::Minus:
                return lhs - rhs;

            case TokenType::Multiply:
                return lhs * rhs;

            case TokenType::Divide:

                if(rhs == 0.0)
                {
                    throw std::runtime_error("Division by zero");
                }

                return lhs / rhs;

            case TokenType::Module:

                if(rhs == 0.0)
                {
                    throw std::runtime_error("Modulo by zero");
                }

                return std::fmod(lhs, rhs);

            case TokenType::Power:
                return std::pow(lhs, rhs);

            default:
                throw std::runtime_error("Unknown operator");
        }
    }
};

#endif