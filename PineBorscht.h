#pragma once
#include "Plant.h"
#include "Animal.h"
class PineBorscht :
    public Plant
{
public:
    PineBorscht(World& world, GridVector position) : Plant(world, position, 10) {
        name = "Pine Borscht";
    }

    // Odziedziczono za poœrednictwem elementu Plant
    virtual std::string toString() override;
    virtual void collision(Organism&) override;
    virtual void action() override;
    virtual void draw() override;
    virtual Plant* clone() override;
};

