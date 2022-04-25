#include "Guarana.h"

std::string Guarana::toString()
{
    return std::string();
}

void Guarana::collision(Organism& other)
{
    if (dynamic_cast<Animal*>(&other)) {
        Animal* animal = dynamic_cast<Animal*>(&other);
        animal->boostStrength(strengthBoost);
        printf("%s got boost %d to strenght by %s\n",
            other.getName().c_str(), strengthBoost, getName().c_str());
    }
}

void Guarana::draw()
{
    printf(";");
}

Plant* Guarana::clone()
{
    return new Guarana(*this);
}
