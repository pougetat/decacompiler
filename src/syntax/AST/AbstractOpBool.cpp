#include "AbstractOpBool.h"

AbstractType * AbstractOpBool::VerifyExpr(
    EnvironmentType * env_types,
    EnvironmentExp * env_exp,
    string * class_name)
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
        m_expr_type = new BooleanType();
        return m_expr_type;
    }

    throw runtime_error("[BOOL OPERATION : BOOLEAN OPERAND EXPECTED]");
}