#pragma once
#include "Organism.h"

class Human;

class HumanSkill : public Object
{
protected:
	bool active;
	int duration;
	int activeTime;
	int cooldownTime;
	int cooldownDuration;
	Human& character;

private:
	void moveAnimal(Organism&, GridVector);

public:

	bool isActive();
	virtual void activate();
	bool isReady();

	HumanSkill(Human& target, int skillDuration = 5, int skillCooldown = 10) : character(target) {
		active = false;
		cooldownTime = 0;
		activeTime = 0;
		duration = skillDuration;
		cooldownDuration = skillCooldown;
		name = "Skill";
	};


	virtual void updateStatus();

	virtual void handleAction() {
	};
	virtual void handleCollision(Organism&) {
	};

	// Odziedziczono za poœrednictwem elementu Object
	virtual std::string toString() override;
	virtual std::string toJSON() override;
};