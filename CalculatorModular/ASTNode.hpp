#ifndef _ASTNODE_HPP
#define _ASTNODE_HPP

class ASTNode
{
public:
    virtual ~ASTNode() = default;

    virtual double evaluate() = 0;
};

#endif