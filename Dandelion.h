#pragma once
#include "Plant.h"
class Dandelion :
    public Plant
{
public:
    Dandelion(World& world, GridVector position) : Plant(world, position, 0) {
        name = "Dandelion";
        numberOfSpreadChances = 3;
    }

    // Odziedziczono za poœrednictwem elementu Plant
    virtual std::string toString() override;
    virtual void action() override;
    virtual void collision(Organism&) override;
    virtual void draw() override;
    virtual Plant* clone() override;

protected:
    int numberOfSpreadChances;
};

