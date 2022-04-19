#include "Fox.h"

std::string Fox::toString()
{
    return std::string();
}

std::string Fox::toJSON()
{
    return std::string();
}

void Fox::draw()
{
    printf("f");
}

Animal* Fox::clone()
{
    return new Fox(*this);
}

void Fox::action()
{
    std::vector<GridVector> moveSpots;
    world.getNeighbourFields(position, moveSpots);
    for (auto it = moveSpots.begin(); it != moveSpots.end();) {

        if (world.isOrganismAtPosition(*it) && world.getFromMap(*it).lock()->getStrength() > strength) {
            it = moveSpots.erase(it);
        }
        else {
            it++;
        }

    }

    if (moveSpots.size() == 0) return;

    int selectedMove = Random::number(moveSpots.size());
    Animal::action(moveSpots[selectedMove]);

}
