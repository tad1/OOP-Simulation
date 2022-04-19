#pragma once
#include "HumanSkill.h"

class Human;

class AlzureShieldSkill :
	public HumanSkill{
public:
	AlzureShieldSkill(Human& human) : HumanSkill(human, 5, 10) {};
	virtual void handleCollision(Organism& other);

	// Odziedziczono za po�rednictwem elementu HumanSkill
	virtual Object* clone() override;
};
