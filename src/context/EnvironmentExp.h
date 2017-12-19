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

        EnvironmentExp();

        void InsertExp(string symbol, ExpDefinition * exp_def);

        ExpDefinition * GetDefinition(string symbol);
};

#endif