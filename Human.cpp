#include "Human.h"

void Human::setDirection(GridVector pos)
{
    moveDirection = pos;
}

void Human::activateSkill(int number)
{
    if (skills.size() < number || skills.size() == 0) return;
    skills[number]->activate();

}

void Human::addSkill(HumanSkill& newSkill)
{
    skills.push_back(&newSkill);
}

std::string Human::toString()
{
    return std::string();
}

std::string Human::toJSON()
{
    return std::string();
}

void Human::collision(Organism& other)
{
    for (auto* skill : skills) {
        skill->handleCollision(other);
    }

    if (!isStuned()) {
        Animal::collision(other);
    }
}

void Human::action()
{
    if (moveDirection == GridVector(0, 0)) return;

    if (world.isPositionValid(position + moveDirection)) {
        Animal::action(position + moveDirection);
    }
}

void Human::draw()
{
    printf("8");
}

Animal* Human::clone()
{
    return new Human(*this);
}
