#ifndef METHOD_EXP_NATURE_H
#define METHOD_EXP_NATURE_H

#include "EnvironmentExp.h"
#include <vector>

using namespace std;

class MethodExpNature : public AbstractExpNature
{

    public:

        EnvironmentExp * m_method_env;

        vector<AbstractType *> * m_signature;

        MethodExpNature();

        EnvironmentExp * GetMethodEnv();

        vector<AbstractType *> * GetMethodSignature();

        void InsertSignatureType(AbstractType * type);

        bool HasSameSignature(MethodExpNature * other_method_exp_nature);

        virtual bool IsParamExpNature();
        virtual bool IsVarExpNature();
        virtual bool IsMethodExpNature();
        virtual bool IsFieldExpNature();
};

#endif