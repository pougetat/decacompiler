#include "DeclClass.h"

void DeclClass::VerifyClassName(EnvironmentType * env_types)
{
    if (env_types->TypeExists(m_class_name->m_symbol))
    {
        throw runtime_error(
            "[DECL CLASS : CLASS '" + m_class_name->m_symbol + "' ALREADY EXISTS]"
        );
    }

    if (m_parent_class_name == NULL)
    {
        m_parent_class_name = new Identifier("Object");
    }

    AddClassToEnvTypes(env_types, m_class_name->m_symbol);
}

void DeclClass::VerifyClassHierarchy(EnvironmentType * env_types)
{   
    if (m_parent_class_name != NULL)
    {
        if (!env_types->TypeExists(m_parent_class_name->m_symbol))
        {
            throw runtime_error(
                "[DECL CLASS : PARENT CLASS '" + m_parent_class_name->m_symbol
                + "' DOES NOT EXIST]"
            );
        }
        SetParentClass(env_types, m_class_name, m_parent_class_name);
    }
}

void DeclClass::VerifyClassMF(EnvironmentType* env_types)
{
    for (DeclField * decl_field : *m_class_fields)
    {
        decl_field->VerifyFieldNoInit(env_types, m_class_name);
    }

    for (DeclMethod * decl_method: *m_class_methods)
    {
        decl_method->VerifyMethodSignature(env_types, m_class_name);
    }
}

void DeclClass::VerifyClassMFHierarchy(EnvironmentType * env_types)
{
    for (DeclField * decl_field : *m_class_fields)
    {
        decl_field->VerifyFieldHierarchy(env_types, m_class_name);
    }
    for (DeclMethod * decl_method : *m_class_methods)
    {
        decl_method->VerifyMethodHierarchy(env_types, m_class_name);
    }
}

void DeclClass::VerifyClassBody(EnvironmentType * env_types)
{
    for (DeclField * decl_field : *m_class_fields)
    {
        decl_field->VerifyFieldInit(env_types, m_class_name);
    }
    for (DeclMethod * decl_method : *m_class_methods)
    {
        decl_method->VerifyMethodBody(env_types, m_class_name);
    }
}

void DeclClass::Display(string tab)
{
    cout << tab << ">" << "[DECL CLASS]" << endl;
    
    m_class_name->Display(tab + "--");
    
    if (m_parent_class_name != NULL)
    {
        m_parent_class_name->Display(tab + "--");
    }

    for (DeclField * decl_field : *m_class_fields)
    {
        decl_field->Display(tab + "--");
    }

    for (DeclMethod * decl_method : *m_class_methods)
    {
        decl_method->Display(tab + "--");
    }
}

void DeclClass::CodeGenDeclClass(
    EnvironmentType * env_types,
    GeneratorEnvironment * gen_env)
{
    gen_env->output_file << ".class public " << m_class_name->m_symbol << endl;

    if (m_parent_class_name->m_symbol == "Object")
    {
        gen_env->output_file << ".super java/lang/Object" << endl;
    }
    else
    {
        gen_env->output_file << ".super " << m_parent_class_name->m_symbol << endl;
    }
}

///////////// PRIVATE METHODS /////////////

void DeclClass::AddClassToEnvTypes(
    EnvironmentType * env_types,
    string parent_class_symbol)
{
    env_types->InsertType(
        m_class_name->m_symbol,
        new TypeDefinition(
            new ClassTypeNature(
                parent_class_symbol
            ),
            new ClassType(m_class_name->m_symbol)
        )
    );
}

void DeclClass::SetParentClass(
    EnvironmentType * env_types,
    Identifier * class_name,
    Identifier * parent_class_name)
{
    // Getting the parent class EnvironmentExp
    
    TypeDefinition * parent_class_type_def =
        env_types->GetTypeDefinition(parent_class_name->m_symbol);

    ClassTypeNature * parent_class_type_nature = (ClassTypeNature *)
        parent_class_type_def->GetTypeNature();

    EnvironmentExp * parent_class_env_exp =
        parent_class_type_nature->GetEnvExp();

    // Getting the current class EnvironmentExp

    TypeDefinition * class_type_def = 
        env_types->GetTypeDefinition(class_name->m_symbol);

    ClassTypeNature * class_type_nature = (ClassTypeNature *)
        class_type_def->GetTypeNature();

    // Setting the parent of the current class to the parent_class

    class_type_nature->SetParentClass(
        parent_class_name->m_symbol,
        parent_class_env_exp
    );
}