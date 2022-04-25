#pragma once
#include "Organism.h"

class Plant :
    public Organism
{
protected:
    int spreadChance; //in %

public:

    Plant(World& world, GridVector position);
    Plant(World& world, GridVector position, int strength);

    // Odziedziczono za pośrednictwem elementu Organism
    virtual void action() override;
    virtual Plant* clone() = 0;
};
