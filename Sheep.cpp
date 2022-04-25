#include "Sheep.h"

std::string Sheep::toString()
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
