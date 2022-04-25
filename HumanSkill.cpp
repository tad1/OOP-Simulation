#include "HumanSkill.h"
#include "Human.h"

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
	cooldownTime -= 1;
	if (cooldownTime <= 0) {
		cooldownTime = 0;
	}
}

std::string HumanSkill::toString()
{
	return name + " is " + (active ? "active" : "disabled") + 
		" cooldown in " + std::to_string(cooldownTime) + 
		" is active for " + std::to_string(activeTime) + "\n";
}

void HumanSkill::writeToFile(std::ofstream& file)
{
	file << " " << active << " ";
	file << activeTime << " ";
	file << cooldownTime;
}

void HumanSkill::readFromFile(std::ifstream& file)
{
	file >> active;
	file >> activeTime;
	file >> cooldownTime;
}

