#pragma once
#include "HumanSkill.h"

class Human;

class AlzureShieldSkill :
	public HumanSkill{
public:
	AlzureShieldSkill(Human& human) : HumanSkill(human, 5, 10) {
		name = "Alzure Shield";
	};

	virtual void handleCollision(Organism& other) override;

	// Odziedziczono za poœrednictwem elementu HumanSkill
	virtual Object* clone() override;
};
