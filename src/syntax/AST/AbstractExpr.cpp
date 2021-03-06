#include "AbstractExpr.h"

void AbstractExpr::VerifyInst(
    EnvironmentType * env_types,
    EnvironmentExp * env_exp,
    string * class_name,
    AbstractType * return_type)
{
    VerifyExpr(env_types, env_exp, class_name);
}

AbstractType * AbstractExpr::VerifyExpr(
    EnvironmentType * env_types,
    EnvironmentExp * env_exp,
    string * class_name
)
{
    throw runtime_error("NOT IMPLEMENTED YET");
}

void AbstractExpr::VerifyRValue(
    EnvironmentType * env_types,
    EnvironmentExp * env_exp,
    string * class_name,
    AbstractType * type)
{
    AbstractType * expr_type = VerifyExpr(
        env_types,
        env_exp,
        class_name
    );
    if (!type->IsSameType(expr_type))
    {
        throw runtime_error("[RVALUE : TYPE MISMATCH]");
    }
}

AbstractType * AbstractExpr::VerifyLValue(
    EnvironmentType * env_types,
    EnvironmentExp * env_exp,
    string * class_name)
{
    throw runtime_error("NOT IMPLEMENTED YET");
}

void AbstractExpr::CodeGenInst(
    EnvironmentType * env_types,
    GeneratorEnvironment * gen_env)
{
    CodeGenExpr(env_types, gen_env);
}