#include "AbstractOpBool.h"

AbstractType * AbstractOpBool::VerifyExpr(
    EnvironmentType * env_types,
    EnvironmentExp * env_exp,
    string class_name)
{
    AbstractType * type_left_operand = m_left_operand->VerifyExpr(
        env_types,
        env_exp,
        class_name
    );
    AbstractType * type_right_operand = m_right_operand->VerifyExpr(
        env_types,
        env_exp,
        class_name
    );

    if (type_left_operand->IsBooleanType() && type_right_operand->IsBooleanType())
    {
        return new BooleanType();
    }

    throw runtime_error("BOOLEAN EXPR : OPERANDS MUST BE OF BOOLEAN TYPE");
}