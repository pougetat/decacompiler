#ifndef ENVIRONMENT_EXP_H
#define ENVIRONMENT_EXP_H

#include <map>
#include <string>
#include <iostream>

#include "ExpDefinition.h"

using namespace std;

class EnvironmentExp
{
    public:
        
        map<string, ExpDefinition *> * m_env_exp;

        EnvironmentExp * m_env_exp_sup;

        string m_englobing_class;

        EnvironmentExp(string class_name);

        void SetParentEnvExp(EnvironmentExp * parent_env_exp);

        EnvironmentExp * GetParentEnv();

        EnvironmentExp * GetMethodEnv(string method_name);

        void InsertExpDefinition(string symbol, ExpDefinition * exp_def);

        bool ContainsSymbol(string symbol);

        bool SupContainsSymbol(string symbol);

        ExpDefinition * GetExpDefinition(string symbol);

        ExpDefinition * GetSupExpDefinition(string symbol);
};

#endif