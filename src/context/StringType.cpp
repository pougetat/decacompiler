#include "StringType.h"

bool StringType::IsBooleanType()
{
    return false;
}

bool StringType::IsFloatType()
{
    return true;
}

bool StringType::IsIntType()
{
    return false;
}

bool StringType::IsStringType()
{
    return true;
}

bool StringType::IsVoidType()
{
    return false;
}