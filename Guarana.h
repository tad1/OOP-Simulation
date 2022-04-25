#pragma once
#include "Plant.h"
#include "Animal.h"
class Guarana :
    public Plant
{
protected:
    int strengthBoost;
public:
    Guarana(World& world, GridVector position) : Plant(world, position, 0) {
        name = "Guarana";
        strengthBoost = 3;
    }

    // Odziedziczono za poœrednictwem elementu Plant
    virtual std::string toString() override;
    virtual void collision(Organism&) override;
    virtual void draw() override;
    virtual Plant* clone() override;
};

