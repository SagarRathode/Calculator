#ifndef _NUMBERNODE_HPP
#define _NUMBERNODE_HPP

#include "ASTNode.hpp"

class NumberNode : public ASTNode
{
private:
    double m_value;

public:
    NumberNode(double value)
        : m_value(value)
    {
    }

    double evaluate() override
    {
        return m_value;
    }
};

#endif