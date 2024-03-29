#pragma once
#include "Plant.h"
#include "Animal.h"
class Wolfberries :
    public Plant
{
public:
    Wolfberries(World& world, GridVector position) : Plant(world, position, 99) {
        name = "Wolfberries";
    }

    // Odziedziczono za pośrednictwem elementu Plant
    virtual std::string toString() override;
    virtual void collision(Organism&) override;
    virtual void draw() override;
    virtual Plant* clone() override;
};

