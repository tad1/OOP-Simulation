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

    void boostStrength(int);
    void stune();
    bool isStuned();

protected:
    bool stuned;
    bool isAnimal(Organism*);
    virtual void action(GridVector position);
    void moveAnimal(Animal&, GridVector);
};

