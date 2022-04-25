#pragma once
#include "Organism.h"
#include "World.h"
class Animal :
    public Organism
    
{
public:
    Animal(World& world, GridVector position);
    Animal(World& world, GridVector position, int initiative, int strength);

    // Odziedziczono za poœrednictwem elementu Organism
    virtual void action() override;
    virtual void collision(Organism& other) override;
    virtual void draw() = 0;
    virtual Animal* clone() = 0;

    virtual void breed(Animal& other);

    //An interface to boost animal stats
    void boostStrength(int);
    void stune();
    bool isStuned();

protected:

    //stuned - a flag that is set to true if an animal is stunned during an attack.
    //A stuned animal cannot attack, or counter attack.
    //At the end of the turn is set to false.
    bool stuned;
    bool isAnimal(Organism*);
    virtual void action(GridVector position);
    void moveAnimal(Animal&, GridVector);
};

