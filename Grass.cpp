#include "Grass.h"

std::string Grass::toString()
{
	return std::string();
}

void Grass::collision(Organism&)
{
}

void Grass::draw()
{
	printf("\"");
}

Plant* Grass::clone()
{
	return new Grass(*this);
}
