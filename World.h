#pragma once
#include "Organism.h"
#include "Vector2D.h"
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <deque>
#include <set>

class OrganismFactory;

class World
{
	typedef std::deque<std::weak_ptr<Organism>> organismQueue;

public:
	World();
	World(GridVector);

	void setSize(int , int);
	GridVector getSize();

	void initialize();
	void clear();

	void drawWorld();
	void updateWorld();

	void addOrganism(Organism*);
	void removeOrganism(Organism*);

	//Moves organism on game map.
	void moveOrganism(GridVector source, GridVector destination);

	void getNeighbourFields(GridVector position, std::vector<GridVector>& vector, int range = 1);
	void getFreeNeighbourFields(GridVector position, std::vector<GridVector>& vector, int range = 1);

	bool isOrganismAtPosition(GridVector);
	bool isPositionValid(GridVector);
	std::weak_ptr<Organism> getFromMap(GridVector);

	void saveWorldStateToFile(std::ofstream& file, OrganismFactory);
	void loadWorldStateFromFile(std::ifstream & file, OrganismFactory);
	void updateExecuteOrder();

protected:
	void addToExecuteOrder(std::weak_ptr<Organism>);
	int getIndexFromPosition(GridVector) const;
	void addExecutionQueueToMap(int key);

	
	/*-----------------------*\
	|*    Data organization	 *|
	\*-----------------------*/

	/*
	* In Organism vector we hold all active organisms
	* In array map we hold key - position, and value - organism
	* In map of queues, we define order of action execution, organisms in queues are in order of seniority.
	*/

	GridVector mapSize;

	std::vector<std::weak_ptr<Organism>> organismsToActivate;

	std::map <int,organismQueue> executeQueue;
	std::weak_ptr<Organism>* map;
	std::vector<std::shared_ptr<Organism>> organisms;
};

