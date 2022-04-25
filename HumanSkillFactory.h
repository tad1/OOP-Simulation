#pragma once
#include "HumanSkill.h"
#include "AlzureShieldSkill.h"

class Human;

/// <summary>
/// A strategic based factory
/// </summary>
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

