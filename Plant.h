#pragma once
#include "Organism.h"

class Plant :
    public Organism
{
protected:
    //described in % of chance for success
    int spreadChance;

public:

    Plant(World& world, GridVector position);
    Plant(World& world, GridVector position, int strength);

    // Odziedziczono za po�rednictwem elementu Organism
    virtual void action() override;
    virtual Plant* clone() = 0;
};
