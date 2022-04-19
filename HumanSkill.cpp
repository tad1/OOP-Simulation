#include "HumanSkill.h"
#include "Human.h"

void HumanSkill::moveAnimal(Organism& animal, GridVector newPosition)
{
	
}

bool HumanSkill::isActive()
{
    return active;
}

void HumanSkill::activate()
{
	if (!isReady()) return;

	active = true;
	activeTime = duration;
	cooldownTime = cooldownDuration;
	printf("Activated %s\n", name.c_str());
}

bool HumanSkill::isReady()
{
    return cooldownTime <= 0;
}

void HumanSkill::updateStatus()
{
	if (active) {
		activeTime -= 1;
		if (activeTime <= 0) {
			activeTime = 0;
			active = false;
		}
	}
	cooldownDuration -= 1;
	if (cooldownDuration <= 0) {
		cooldownDuration = 0;
	}
}

std::string HumanSkill::toString()
{
	return std::string();
}

std::string HumanSkill::toJSON()
{
	return std::string();
}

