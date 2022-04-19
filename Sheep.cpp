#include "Sheep.h"

std::string Sheep::toString()
{
    return std::string();
}

std::string Sheep::toJSON()
{
    return std::string();
}

void Sheep::draw()
{
    std::cout << "o";
}

Animal* Sheep::clone()
{
    return new Sheep(*this);
}
