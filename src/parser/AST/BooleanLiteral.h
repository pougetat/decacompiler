#ifndef BOOLEAN_LITERAL_H
#define BOOLEAN_LITERAL_H

#include "AbstractExpr.h"

class BooleanLiteral : public AbstractExpr
{
    public:
        
        bool m_value;

        BooleanLiteral(bool value);
        void Display(string tab);
};

#endif