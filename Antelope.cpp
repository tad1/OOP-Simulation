#include "Antelope.h"

std::string Antelope::toString()
{
    return std::string();
}

void Antelope::action()
{
    std::vector<GridVector> avalibleMoves;
    world.getNeighbourFields(position, avalibleMoves, moveRange);
    if (avalibleMoves.size() == 0) return;

    int selectedMove = Random::number(avalibleMoves.size());
    GridVector newPosition = avalibleMoves[selectedMove];

    Animal::action(newPosition);
}

void Antelope::collision(Organism& other)
{
    if (isAnimal(&other) && !compare(other) && Random::chance(50)) {

        std::vector<GridVector> freeSpots;
        world.getFreeNeighbourFields(position, freeSpots, 2);
        if (freeSpots.size() != 0) {
            
            Animal* animal = dynamic_cast<Animal*>(&other);
            animal->stune();

            int selectedMove = Random::number(freeSpots.size());
            GridVector newPos = freeSpots[selectedMove];
            world.moveOrganism(position, newPos);
            position = newPos;

        }
    }
    Animal::collision(other);

}

void Antelope::draw()
{
    printf("a");
}

Animal* Antelope::clone()
{
    return new Antelope(*this);
}
