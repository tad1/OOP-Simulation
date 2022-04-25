#include "PineBorscht.h"

std::string PineBorscht::toString()
{
	return std::string();
}

void PineBorscht::collision(Organism& organism)
{
    if (dynamic_cast<Animal*>(&organism)) {
		organism.kill();
		kill();
		printf("%s has been eated by %s. The %s killed %s\n",
			getName().c_str(), organism.getName().c_str(),
			getName().c_str(), organism.getName().c_str());
		world.removeOrganism(this);
	}
}

void PineBorscht::action()
{
	std::vector<GridVector> killingSpots;
	world.getNeighbourFields(position,killingSpots);

	for (auto& x : killingSpots) {
		if (world.isOrganismAtPosition(x)) {
			auto wp = world.getFromMap(x);
			auto sp = wp.lock();
			if (dynamic_cast<Animal*>(sp.get())) {
				sp->kill();
				world.removeOrganism(sp.get());
				printf("%s was killed by %s\n",
					sp->getName().c_str(), getName().c_str());
			}
		}
	}

	Plant::action();
}

void PineBorscht::draw()
{
    printf("%%");
}

Plant* PineBorscht::clone()
{
    return new PineBorscht(*this);
}