#include "Dandelion.h"

std::string Dandelion::toString()
{
    return std::string();
}

std::string Dandelion::toJSON()
{
    return std::string();
}

void Dandelion::action()
{
    for (int i = 0; i < numberOfSpreadChances; i++) {
        Plant::action();
    }
}

void Dandelion::collision(Organism&)
{
}

void Dandelion::draw()
{
    printf("!");
}

Plant* Dandelion::clone()
{
    return new Dandelion(*this);
}
