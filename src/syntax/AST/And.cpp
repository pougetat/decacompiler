#include "And.h"

And::And(AbstractExpr * e1, AbstractExpr * e2)
{
    m_left_operand = e1;
    m_right_operand = e2;
}

AbstractExpr * And::Clone()
{
    return new And(
        m_left_operand->Clone(),
        m_right_operand->Clone()
    );
}

void And::Display(string tab)
{
    cout << tab << ">" << "[AND]" << endl;
    m_left_operand->Display(tab + "--");
    m_right_operand->Display(tab + "--");
}