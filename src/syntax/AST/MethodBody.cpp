#include "MethodBody.h"

MethodBody::MethodBody(
    vector<DeclVar *> * list_decl_var,
    vector<AbstractInst *> * list_inst)
{
    m_list_decl_var = list_decl_var;
    m_list_inst = list_inst;
}

void MethodBody::Display(string tab)
{
    cout << tab << ">" << "[METHOD BODY]" << endl;
    cout << tab << "-->" << "[LIST DECL VAR]" << endl;
    for (DeclVar * decl_var : *m_list_decl_var)
    {
        decl_var->Display(tab + "----");
    }
    cout << tab << "-->" << "[LIST INST]" << endl;
    for (AbstractInst * inst : *m_list_inst)
    {
        inst->Display(tab + "----");
    }
}