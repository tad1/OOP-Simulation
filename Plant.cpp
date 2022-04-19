#include "Plant.h"
#include "World.h"
#include <vector>

Plant::Plant(World& world, GridVector position) : Organism(world,position)
{
	name = "Plant";
	spreadChance = 20;
	
}

Plant::Plant(World& world, GridVector position, int strength) : Organism(world,position,0,strength)
{
	name = "Plant";
	spreadChance = 20;
}

void Plant::action()
{
	if (Random::chance(spreadChance)) {
		std::vector<GridVector> avalibleSpots;
		world.getFreeNeighbourFields(position, avalibleSpots);
		if (avalibleSpots.size() == 0) return;

		int selectedSpot = Random::number(avalibleSpots.size());
		GridVector seedPosition = avalibleSpots[selectedSpot];

		Plant* descendor = clone();
		descendor->setPosition(seedPosition);
		world.addOrganism(descendor);

		printf("%s has spreeded.\n",getName().c_str());

	}
}

Plant* Plant::clone()
{
	return nullptr;
}
