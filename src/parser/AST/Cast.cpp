#include "Cast.h"

Cast::Cast(Identifier * cast_type, AbstractExpr * expr)
{
    m_cast_type = cast_type;
    m_expr = expr;
}

AbstractExpr * Cast::Clone()
{
    return new Cast(
        new Identifier(m_cast_type->m_symbol),
        m_expr->Clone()
    );
}

void Cast::Display(string tab)
{
    cout << tab << ">" << "[CAST]" << endl;
    m_cast_type->Display(tab + "--");
    m_expr->Display(tab + "--");
}