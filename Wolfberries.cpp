#include "Wolfberries.h"

std::string Wolfberries::toString()
{
	return std::string();
}

void Wolfberries::collision(Organism& organism)
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

void Wolfberries::draw()
{
	printf("x");
}

Plant* Wolfberries::clone()
{
	return new Wolfberries(*this);
}
