#pragma once
#include "Animal.h"
class Fox :
    public Animal
{
public:
    Fox(World& world, GridVector position) : Animal(world, position, 7,3)  {
		name = "Fox";
	};

    // Odziedziczono za poœrednictwem elementu Animal
    virtual std::string toString() override;
    virtual void draw() override;
    virtual Animal* clone() override;
    virtual void action() override;
};

