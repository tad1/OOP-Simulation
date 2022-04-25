#pragma once
#include "Animal.h"
class Sheep : public Animal
{
public:
	Sheep(World& world, GridVector position) : Animal(world, position, 4, 4)  {
		name = "Sheep";
	};

	// Odziedziczono za po�rednictwem elementu Animal
	virtual std::string toString() override;
	virtual void draw() override;
	virtual Animal* clone() override;
};

