#ifndef NOT_H
#define NOT_H

#include "AbstractUnaryExpr.h"

class Not : public AbstractUnaryExpr
{
    public:
        
        AbstractExpr * m_expr;

        Not(AbstractExpr * expr);
        AbstractExpr * Clone();
        void Display(string tab);
};

#endif