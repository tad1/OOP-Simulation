#pragma once
#include "Animal.h"
class Turtle :
    public Animal
{
public:
	Turtle(World& world, GridVector position) : Animal(world, position, 1, 2)  {
		name = "Turtle";
	};


	// Odziedziczono za poœrednictwem elementu Animal
	virtual std::string toString() override;

	virtual std::string toJSON() override;

	virtual void draw() override;

	virtual Animal* clone() override;

	virtual void action() override;
	virtual void collision(Organism&) override;

};

