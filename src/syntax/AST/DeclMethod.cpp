#include "DeclMethod.h"

void DeclMethod::VerifyMethodSignature(
    EnvironmentType * env_types,
    Identifier * class_name)
{
    if (!env_types->TypeExists(m_return_type->m_symbol))
    {
        throw runtime_error(
            "[RETURN TYPE : UNKNOWN TYPE '" + m_return_type->m_symbol + "']"
        );
    }

    InsertMethodExpDefinition(env_types, class_name);
    VerifyParamTypes(env_types, class_name);
}

void DeclMethod::VerifyMethodHierarchy(
    EnvironmentType * env_types,
    Identifier * class_name)
{
    EnvironmentExp * class_env_exp = 
        env_types->GetClassEnvExp(class_name->m_symbol);

    if (class_env_exp->SupContainsSymbol(m_name->m_symbol))
    {
        ExpDefinition * cur_exp =
            class_env_exp->GetExpDefinition(m_name->m_symbol);

        ExpDefinition * sup_exp = 
            class_env_exp->GetSupExpDefinition(m_name->m_symbol);

        if (!sup_exp->GetTypeNature()->IsMethodExpNature())
        {
            throw runtime_error(
              "[DECL METHOD : PARENT IDENTIFIER SHOULD BE OF SAME TYPE]"
            );
        }

        MethodExpNature * sup_method_exp_nature =
            (MethodExpNature *) sup_exp->GetTypeNature();

        MethodExpNature * cur_method_exp_nature =
            (MethodExpNature *) cur_exp->GetTypeNature();

        if (!sup_method_exp_nature->HasSameSignature(cur_method_exp_nature))
        {
            throw runtime_error(
                "[DECL METHOD : PARENT METHOD DOES NOT HAVE SAME SIGNATURE]"
            );
        }

        env_types->IsSubType(m_return_type->m_symbol, sup_exp->GetType());
    }
}

void DeclMethod::VerifyMethodBody(
    EnvironmentType * env_types,
    Identifier * class_name)
{
    MethodExpNature * method_exp_nature = 
        InitMethodEnv(env_types, class_name);

    m_body->VerifyMethodBody(
        env_types,
        env_types->GetClassEnvExp(class_name->m_symbol),
        method_exp_nature->GetMethodEnv(),
        &(class_name->m_symbol),
        env_types->GetType(m_return_type->m_symbol)
    );
}

void DeclMethod::Display(string tab)
{
    cout << tab << ">" << "[DECL METHOD]" << endl;

    m_return_type->Display(tab + "--");
    m_name->Display(tab + "--");
    
    cout << tab << "-->" << "[LIST PARAM]" << endl;
    for (DeclParam * decl_param : *m_params)
    {
        decl_param->Display(tab + "----");
    }

    m_body->Display(tab + "--");
}

void DeclMethod::CodeGenDeclMethod(
    EnvironmentType * env_types,
    GeneratorEnvironment * gen_env)
{
    CodeGenMethodHeader(env_types, gen_env);
    m_body->CodeGenMethodBody(env_types, gen_env);
    gen_env->output_file << ".end method" << endl;
}

///////////// PRIVATE METHODS /////////////

void DeclMethod::VerifyParamTypes(
    EnvironmentType * env_types,
    Identifier * class_name)
{
    for (DeclParam * param : *m_params)
    {
        param->VerifyDeclParam(env_types, class_name, m_name);
    }
}

void DeclMethod::InsertMethodExpDefinition(
    EnvironmentType * env_types,
    Identifier * class_name)
{
    EnvironmentExp * class_env_exp = 
    env_types->GetClassEnvExp(class_name->m_symbol);

    class_env_exp->InsertExpDefinition(
        m_name->m_symbol,
        new ExpDefinition(
            new MethodExpNature(class_name->m_symbol),
            env_types->GetType(m_return_type->m_symbol)
        )
    );
}

MethodExpNature * DeclMethod::InitMethodEnv(
    EnvironmentType * env_types,
    Identifier * class_name)
{
    ExpDefinition * method_exp = env_types
        ->GetClassEnvExp(class_name->m_symbol)
        ->GetExpDefinition(m_name->m_symbol);
    
    MethodExpNature * method_exp_nature = 
        (MethodExpNature *) method_exp->GetTypeNature();

    EnvironmentExp * method_env =
        method_exp_nature->GetMethodEnv();

    // Setting the parent of the Method Environment

    method_env->SetParentEnvExp(env_types->GetClassEnvExp(class_name->m_symbol));

    // Adding the parameters to the Method Environment

    for (DeclParam * param : *m_params)
    {
        method_env->InsertExpDefinition(
            param->m_param_name->m_symbol,
            new ExpDefinition(
                new ParamExpNature(),
                env_types->GetType(param->m_param_type->m_symbol)
            )
        );
    }
    return method_exp_nature;
}

void DeclMethod::CodeGenMethodHeader(
    EnvironmentType * env_types,
    GeneratorEnvironment * gen_env)
{
    // method signature in jasmin
    
    AbstractType * return_type = env_types->GetType(m_return_type->m_symbol);

    gen_env->output_file 
        << ".method " 
        << m_name->m_symbol << "(";
    for (DeclParam * decl_param : *m_params)
    {
        decl_param->CodeGenDeclParam(env_types, gen_env);
    }
    gen_env->output_file << ")";
    gen_env->output_file << return_type->JasminSymbol() << endl;

    // stack limit and locals limit
    gen_env->output_file << "    .limit stack 10" << endl;
    gen_env->output_file << "    .limit locals 10" << endl;
}