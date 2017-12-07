#ifndef ABSTRACT_READ_EXPR_H
#define ABSTRACT_READ_EXPR_H

#include "AbstractExpr.h"

class AbstractReadExpr : public AbstractExpr
{
    public:
        virtual void Display(string tab) = 0;
        
        // CONTEXT CHECKING RELATED METHODS
        
        virtual AbstractType * VerifyExpr(
            EnvironmentType * env_types,
            EnvironmentExp * env_exp,
            string class_name
        );
};

#endif