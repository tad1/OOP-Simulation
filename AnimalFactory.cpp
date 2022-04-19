#include "AnimalFactory.h"

int AnimalFactory::getOrganismType(Organism* organism)
{
	if (dynamic_cast<Animal*>(organism)) {
		return getAnimalType(dynamic_cast<Animal*>(organism));
	}
	else if(dynamic_cast<Plant*>(organism)) {
		return getPlantType(dynamic_cast<Plant*>(organism)) + ANIMAL_COUNT;
	}
	return -1;
}

int AnimalFactory::getAnimalType(Animal* animal)
{
	if (dynamic_cast<Antelope*>(animal)) {
		return ANTELOPE;
	} 
	else if (dynamic_cast<Fox*>(animal)) {
		return FOX;
	}
	else if (dynamic_cast<Sheep*>(animal)) {
		return SHEEP;
	}
	else if (dynamic_cast<Turtle*>(animal)) {
		return TURTLE;
	}
	else if (dynamic_cast<Wolf*>(animal)) {
		return WOLF;
	}
	else if (dynamic_cast<Human*>(animal)) {
		return ANIMAL_COUNT;
	}
	return -1;
}

int AnimalFactory::getPlantType(Plant* plant)
{
	if (dynamic_cast<Dandelion*>(plant)) {
		return DANDELION;
	} 
	else if (dynamic_cast<Grass*>(plant)) {
		return GRASS;
	}
	else if (dynamic_cast<Guarana*>(plant)) {
		return GURANA;
	}
	else if (dynamic_cast<PineBorscht*>(plant)) {
		return PINE_BORSCHT;
	}
	else if (dynamic_cast<Wolfberries*>(plant)) {
		return WOLFBERRIES;
	}
	return -1;
}


Organism* AnimalFactory::createOrganism(int id, GridVector pos)
{
	if (id < ANIMAL_COUNT) {
		return createAnimal(id, pos);
	}
	else if (id < ANIMAL_COUNT + PLANT_COUNT) {
		return createPlant(id - ANIMAL_COUNT, pos);
	}
	else if (id < ANIMAL_COUNT + PLANT_COUNT + HUMAN_COUNT) {
		return new Human(world, pos);
	}
	return nullptr;
}

Organism* AnimalFactory::createPlant(int plantId, GridVector pos)
{
	Organism* organism;
	switch (plantId)
	{
	case DANDELION:
		organism = new Dandelion(world, pos);
		break;
	case GRASS:
		organism = new Grass(world, pos);
		break;
	case GURANA:
		organism = new Guarana(world, pos);
	case PINE_BORSCHT:
		organism = new PineBorscht(world, pos);
		break;
	case WOLFBERRIES:
		organism = new Wolfberries(world, pos);
		break;
	default:
		organism = nullptr;
		break;
	}

	return organism;
}

Organism* AnimalFactory::createPlant(int plantId, GridVector pos, int strength, int initiative)
{
	Organism* organism = createPlant(plantId, pos);
	organism->setParamters(strength, initiative);
	return organism;
}

Organism* AnimalFactory::createAnimal(int AnimalId, GridVector pos)
{
	Organism* organism;
	switch (AnimalId)
	{
	case ANTELOPE:
		organism = new Antelope(world, pos);
		break;
	case FOX:
		organism = new Fox(world, pos);
		break;
	case SHEEP:
		organism = new Sheep(world, pos);
		break;
	case TURTLE:
		organism = new Turtle(world, pos);
		break;
	case WOLF:
		organism = new Wolf(world, pos);
		break;
	default:
		organism = nullptr;
		break;
	}

	return organism;
}

Organism* AnimalFactory::createAnimal(int AnimalId, GridVector pos, int strength, int initiative)
{
	Organism* organism = createAnimal(AnimalId, pos);
	organism->setParamters(strength, initiative);
	return organism;
}

