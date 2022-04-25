#pragma once
#include "HumanSkill.h"
#include "AlzureShieldSkill.h"

class Human;

//A facade and abstract factory that creates (or returns id) organism based on the given id.
//Named "Factory" to simplify the name.
class HumanSkillFactory
{
	Human& client;

public:
	enum HumanSkillName {
		ALZURE_SHIELD
	};

	HumanSkillFactory(Human& client) : client(client) {
	}

	int getSkillId(HumanSkill*);
	HumanSkill* createSkill(int id);
};

