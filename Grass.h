#pragma once
#include "Plant.h"
class Grass :
    public Plant
{
public:
    Grass(World& world, GridVector position) : Plant(world, position, 0) {
        name = "Grass";
    }

    // Odziedziczono za poœrednictwem elementu Plant
    virtual std::string toString() override;
    virtual void collision(Organism&) override;
    virtual void draw() override;
    virtual Plant* clone() override;
};

