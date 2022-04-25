#include "Organism.h"
#include <fstream>
#include <sstream>


void Organism::setPosition(GridVector newPosition)
{
	position = newPosition;
}

Organism::Organism(World& wrld, GridVector pos) : Organism(wrld, pos, 0 ,0)
{}


Organism::Organism(World& wrld, GridVector pos, int init, int str) :world(wrld)
{
	alive = true;
	initiative = init;
	strength = str;
	position = pos;
	name = "Organism";
}

void Organism::kill()
{
	alive = false;
}

bool Organism::isAlive()
{
	return alive;
}

void Organism::writeToFile(std::ofstream& file)
{
	file << position.x << " " << position.y << " ";
	file << strength << " " << initiative;
}

void Organism::readFromFile(std::ifstream& file)
{
	GridVector setPosition;
	int type;

	file >> type;
	file >> setPosition.x;
	file >> setPosition.y;
	file >> strength;
	file >> initiative;

	position = setPosition;
}
