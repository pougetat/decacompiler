#ifndef ABSTRACT_LITERAL_H
#define ABSTRACT_LITERAL_H

#include "AbstractExpr.h"

class AbstractLiteral : public AbstractExpr
{
	public:
		
        virtual AbstractType * VerifyExpr(
            EnvironmentType * env_types,
            EnvironmentExp * env_exp,
            string * class_name
        );

        virtual void CodeGenExpr(
            EnvironmentType * env_types,
            GeneratorEnvironment * gen_env
        );      
};

#endif