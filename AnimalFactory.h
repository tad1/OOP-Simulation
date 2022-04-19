#pragma once
#include "IncludeAllOrganisms.h"
#include "Human.h"
#include <vector>

class AnimalFactory {
	std::vector<Organism*> organimsms;
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

	AnimalFactory(World& wrld) : world(wrld) {
	}

	int getOrganismType(Organism*);
	int getAnimalType(Animal*);
	int getPlantType(Plant*);

	Organism* createOrganism(int id, GridVector pos);
	Organism* createPlant(int plantId, GridVector pos);
	Organism* createPlant(int plantId, GridVector pos, int strength, int initiative);
	Organism* createAnimal(int AnimalId, GridVector pos);
	Organism* createAnimal(int AnimalId, GridVector pos, int strength, int initiative);
};

