#pragma once
#include "Organism.h"

class Human;

//An universal recipe for skill.
//Each skill in simulation have active and cooldown time.
//As the names are self-explanatory, the worth mention idea is that cooldown-duration can be shorter than active-time
class HumanSkill : public Object, public ISaveable
{
protected:
	bool active;
	int duration;
	int activeTime;
	int cooldownTime;
	int cooldownDuration;
	Human& character;

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

	// Odziedziczono za poœrednictwem elementu ISaveable
	virtual void writeToFile(std::ofstream&) override;
	virtual void readFromFile(std::ifstream&) override;
};