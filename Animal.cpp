#include "Animal.h"
#include "Plant.h"
#include <vector>

void Animal::moveAnimal(Animal& animal, GridVector newPosition)
{
    world.moveOrganism(animal.position, newPosition);
    animal.position = newPosition;
}

Animal::Animal(World& world, GridVector position) : Organism(world,position)
{
    name = "Animal";
}

Animal::Animal(World& world, GridVector position, int initiative, int strength) : Organism(world,position,initiative,strength)
{
    name = "Animal";
}

void Animal::action()
{
    std::vector<GridVector> possibleDirections;
    world.getNeighbourFields(position, possibleDirections);
    if (possibleDirections.size() == 0) return;

    int selectedMove = Random::number(0, possibleDirections.size());
    GridVector newPos = possibleDirections[selectedMove];
   
    action(newPos);
    
}

bool Animal::isAnimal(Organism* organism)
{
    return dynamic_cast<Animal*>(organism);
}

void Animal::action(GridVector newPos)
{
    if (position == newPos) {
        return;
    }

    if (world.isOrganismAtPosition(newPos)) {
        //collision
        std::weak_ptr<Organism> wp = world.getFromMap(newPos);
        std::shared_ptr<Organism> sp = wp.lock();
        Organism& other = *sp.get();
        
        other.collision(*this);
        if (isAlive() && !isStuned()) {
            if (!compare(other)) {
                if (strength >= other.getStrength()) {
                    other.kill();
                    world.removeOrganism(&other);
                    

                    if (dynamic_cast<Animal*>(&other)) {
                        printf("A %s attacked %s. The %s died in this fight.\n",this->getName().c_str(), other.getName().c_str(), other.getName().c_str());
                    }
                    else if (dynamic_cast<Plant*>(&other)) {
                        printf("The %s has been eaten by %s\n", other.getName().c_str(), getName().c_str());
                    }

                }
            }
            else {
                //Organism breeded
                return;
            }
        }
        else if(!isAlive()) {
            world.removeOrganism(this);
            return;
        }

        if (isStuned()) {
            stuned = false;
            return;
        }

    }

    world.moveOrganism(position, newPos);
    position = newPos;

}

void Animal::collision(Organism& other)
{
    if (this->compare(&other)) {
        breed(*dynamic_cast<Animal*>(&other));
    }
    else {
        if (strength > other.getStrength()) {
            other.kill();
            printf("A %s attacked %s. The %s died in this fight.\n",other.getName().c_str(), this->getName().c_str(), other.getName().c_str());
        }
    }
}

void Animal::breed(Animal& other)
{
    std::vector<GridVector> possibleDirections;
    world.getFreeNeighbourFields(position, possibleDirections);

    if (possibleDirections.size() == 0) return;
    int selectedMove = Random::number(0, possibleDirections.size());
    GridVector newPos = possibleDirections[selectedMove];
    
    Animal* child = clone();
    //because private is only in context per object in c++, this is legal
    child->setPosition(newPos);
    child->strength = (strength + other.strength) / 2;
    child->initiative = (initiative + other.initiative) / 2;
    world.addOrganism(child);

    printf("A new %s has been borned\n",child->getName().c_str());
}

void Animal::boostStrength(int amount)
{
    strength += amount;
}

void Animal::stune()
{
    stuned = true;
}

bool Animal::isStuned()
{
    return stuned;
}
