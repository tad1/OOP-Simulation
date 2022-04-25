#pragma once
#include "IncludeAllOrganisms.h"
#include "Human.h"
#include <vector>

//A facade and abstract factory that creates (or returns id) organism based on the given id.
//Named "Factory" to simplify the name.
class OrganismFactory {
public:

	World& world;

	enum AnimalName
	{
		ANTELOPE, FOX, SHEEP, TURTLE, WOLF, ANIMAL_COUNT
	};

	enum PlantName
	{
		DANDELION, GRASS, GURANA, PINE_BORSCHT, WOLFBERRIES, PLANT_COUNT
	};

	enum HumanName {
		HUMAN, HUMAN_COUNT
	};

	OrganismFactory(World& wrld) : world(wrld) {
	}

	int getOrganismType(Organism*);
	int getAnimalType(Animal*);
	int getPlantType(Plant*);

	Organism* createOrganism(int id, GridVector pos);
	Organism* createPlant(int plantId, GridVector pos);
	Organism* createAnimal(int AnimalId, GridVector pos);
};

