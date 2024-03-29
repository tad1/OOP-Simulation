#pragma once
#include "Animal.h"
class Wolf :
    public Animal 
{
public:
    Wolf(World& world, GridVector position) : Animal(world, position, 5, 9) {
        name = "Wolf";
    };

    // Odziedziczono za pośrednictwem elementu Animal
    virtual std::string toString() override;
    virtual void draw() override;
    virtual Animal* clone() override;
};

