#include "Wolf.h"

std::string Wolf::toString()
{
    return std::string();
}

void Wolf::draw()
{
    printf("w");
}

Animal* Wolf::clone()
{
    return new Wolf(*this);
}
