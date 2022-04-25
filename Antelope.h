#pragma once
#include "Animal.h"
class Antelope :
    public Animal
{
protected:
	int moveRange;

public:
	Antelope(World& world, GridVector position) : Animal(world, position, 4, 4)  {
		name = "Antelope";
		moveRange = 2;
	};

	// Odziedziczono za poœrednictwem elementu Animal
	virtual std::string toString() override;

	virtual void action() override;
	virtual void collision(Organism&) override;
	virtual void draw() override;

	virtual Animal* clone() override;
};

