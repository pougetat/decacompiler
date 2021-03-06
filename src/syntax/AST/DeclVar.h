#ifndef DECL_VAR_H
#define DECL_VAR_H

#include "Identifier.h"
#include "AbstractInitialization.h"
#include "../../context/EnvironmentType.h"
#include "../../context/EnvironmentExp.h"
#include "../../context/ExpDefinition.h"
#include "../../context/VarExpNature.h"

class DeclVar {

    public:

        Identifier * m_type;
        
        Identifier * m_symbol;
        
        AbstractInitialization * m_init;

        void Display(string tab);
        
        void VerifyDeclVar(
            EnvironmentType * env_types,
            EnvironmentExp * env_exp,
            string * class_name
        );

        void CodeGenExpr(
            EnvironmentType * env_types,
            GeneratorEnvironment * gen_env
        );
};

#endif