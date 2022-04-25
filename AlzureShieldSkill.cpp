#include "AlzureShieldSkill.h"
#include "Human.h"

void AlzureShieldSkill::handleCollision(Organism& other)
{
    if (character.isAnimal(&other)) {
        std::vector<GridVector> avalibleSpots;
        character.world.getFreeNeighbourFields(character.position,avalibleSpots);

        Animal* animal = dynamic_cast<Animal*>(&other);
        animal->stune();

        //if human is stuned, then he won't attact animal
        character.stune();

        printf("%s used %s against %s\n",
            character.getName().c_str(),
            getName().c_str(), other.getName().c_str());

        if (avalibleSpots.size() == 0) return;

        int selectedMove = Random::number(avalibleSpots.size());

        character.moveAnimal(*animal, avalibleSpots[selectedMove]);
    }
}

Object* AlzureShieldSkill::clone()
{
    return new AlzureShieldSkill(*this);
}
