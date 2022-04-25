#pragma once
#include "World.h"
#include "IncludeAllOrganisms.h"
#include "OrganismFactory.h"
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <algorithm>

//A facade for simulation, with GUI. Handle save, and world generation system.
class Simulation
{
public:
	struct WorldMeta {
		std::string name;
		unsigned int seed;
	};

protected:

	enum GUIState
	{
		MAIN = 0, LOAD, NEW, EXIT, PLAY
	} currentState;

	World world;
	WorldMeta worldInfo;
	OrganismFactory organismFactory;

	//SaveInfo contains information about all saves
	bool readSaveInfo(std::vector<WorldMeta>& saveInfo);
	void writeSaveInfo(std::vector<WorldMeta>& saveInfo);

	void readWorld(std::string path);
	void writeWorldSave();
	void drawInfo();
	void drawMenu();
	void handleMenu();
	void handleLoad();
	void handleNewGame();
	void drawSelectSaved(std::vector<WorldMeta>& worldInfo);

public:

	Simulation() :organismFactory(world) {
		currentState = MAIN;
	};

	void showGUI();
	void play();

	void generateWorld();
	
	void saveSimulation();
	void readSimulation(WorldMeta info);

};

