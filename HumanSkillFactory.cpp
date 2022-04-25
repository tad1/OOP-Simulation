#include "HumanSkillFactory.h"

int HumanSkillFactory::getSkillId(HumanSkill* skill)
{
	if (dynamic_cast<AlzureShieldSkill*>(skill)) {
		return ALZURE_SHIELD;
	}

	return -1;
}

HumanSkill* HumanSkillFactory::createSkill(int id)
{
	switch (id)
	{
	case ALZURE_SHIELD:
		return new AlzureShieldSkill(client);
		break;
	}
    return nullptr;
}
