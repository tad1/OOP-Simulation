#include "Turtle.h"

std::string Turtle::toString()
{
    return std::string();
}

std::string Turtle::toJSON()
{
    return std::string();
}

void Turtle::draw()
{
    printf("t");
}

Animal* Turtle::clone()
{
    return new Turtle(*this);
}

void Turtle::action()
{
    if (Random::chance(25)) {
        Animal::action();
    }
}

void Turtle::collision(Organism& other)
{
    if (isAnimal(&other) && !compare(other) && other.getStrength() < 5) {
        Animal* animal = dynamic_cast<Animal*>(&other);
        animal->stune();
        printf("%s stuned %s\n", this->getName().c_str(), other.getName().c_str());
    }

    Animal::collision(other);
}
