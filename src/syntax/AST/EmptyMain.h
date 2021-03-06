#ifndef EMPTY_MAIN_H
#define EMPTY_MAIN_H

#include "AbstractMain.h"
#include <iostream>

using namespace std;

class EmptyMain : public AbstractMain
{
    public:

        void Display(string tab);

        EnvironmentExp * VerifyMain(EnvironmentType * env_types);

        void CodeGenMain(
            EnvironmentType * env_types,
            GeneratorEnvironment * gen_env
        );
};

#endif