#include "Simulation.h"
#include "Input.h"

bool Simulation::readSaveInfo(std::vector<WorldMeta>& saveInfo)
{
	saveInfo.clear();
	std::ifstream file("data/saveinfo.meta", std::ios::in);
	if (!file) {
		return true;
	}

	std::string line;
	std::string value;

	int counterMod = 2; //specifies how many values file should contain
	int valueCounter = 0; //a counter for mentioned values
	WorldMeta currentInfo;

	//this implementation could be much simpler
	//but to add a little more challenge to project I decided to store information in csv format
	while (std::getline(file, line)) {
		std::stringstream lstream(line);

		while (std::getline(lstream, value, ',')) {
			switch (valueCounter)
			{
			case 0:
				currentInfo.name = value;
				break;
			case 1:
				currentInfo.seed = std::stoi(value);
				saveInfo.push_back(currentInfo);
				break;
			default:
				break;
			}
			valueCounter = (++valueCounter % 2);
		}
	}

	file.close();

	if (valueCounter != 0) {
		printf("File 'saveinfo.meta' has been corrupted.\n");
		saveInfo.clear();
		return 1;
	}
	return 0;

}

void Simulation::writeSaveInfo(std::vector<WorldMeta>& saveInfo)
{
	std::ofstream file("data/saveinfo.meta", std::ios::out | std::ios::trunc);
	if (!file.is_open()) return;
	
	for (auto& info : saveInfo) {
		file << info.name << "," << info.seed << std::endl;
	}
	file.close();
}

void Simulation::readWorld(std::string path)
{
	std::ifstream file(path, std::ios::in);
	if (!file.is_open()) {
		throw LoadExeption("couldn't open selected save file.");
	};
	unsigned int seed;
	size_t count;
	
	file >> seed;
	file >> count;

	Random::setSeed(seed);
	for (int i = 0; i < count; i++) {
		Random::randi();
	}

	try {
		world.loadWorldStateFromFile(file, organismFactory);
	}
	catch (const LoadExeption& e) {
		file.close();
		throw;
	}

	file.close();
}

void Simulation::writeWorldSave()
{
	std::string path = "data/" + worldInfo.name + ".save";
	std::ofstream file(path, std::ios::out | std::ios::trunc);
	if (!file.is_open()) return;

	file << worldInfo.seed <<" " << Random::getCount() << std::endl;

	world.saveWorldStateToFile(file, organismFactory);

	file.close();
}

void Simulation::drawInfo()
{
	printf("Virtual World by Tadeusz Brzeski 191343\n");
	if(currentState == PLAY)
		printf("World name: %s     Seed: %d\n", worldInfo.name.c_str(), worldInfo.seed);
}

void Simulation::drawMenu()
{
	system("cls");
	drawInfo();
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~  Welcome To Virtual World  ~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");
	printf("N - new simulation\n");
	printf("L - load saved simulation\n");
	printf("Q - quit\n");
}

void Simulation::handleMenu()
{
			drawMenu();
			char input;
			std::cin >> input;
			if (input == 'n') {
				currentState = GUIState::NEW;
			}
			else if (input == 'l') {
				currentState = LOAD;
			}
			else if (input == 'q') {
				currentState = EXIT;
			}

}

void Simulation::handleLoad()
{
	std::vector<WorldMeta> saves;
	bool isCorrupted = readSaveInfo(saves);

	drawSelectSaved(saves);
	int selectedWorld;
	printf("\n Select world:");
	std::cin >> selectedWorld;

	if (selectedWorld == saves.size() || selectedWorld == 'q') {
		currentState = GUIState::MAIN;
	}
	else if (selectedWorld >= 0 && selectedWorld < saves.size()) {
		currentState = GUIState::PLAY;
		try {
			readSimulation(saves[selectedWorld]);
		}
		catch (const LoadExeption& e) {
			printf("Load Falied: %s\n", e.what());
			printf("Press any key to continue:");
			Input::getKey();
			currentState = GUIState::LOAD;
		}
	}
	else {
		printf("Selected invalid save!\n");
		Input::getKey();
	}
}

void Simulation::handleNewGame()
{
	int width, heigth;
	std::string name;
	unsigned int seed;

	seed = Random::randi();
	Random::setSeed(seed);
	Random::randi();
	seed = Random::randi();

	std::getline(std::cin, name);

	system("cls");
	drawInfo();
	printf("Starting new world\n\n");

	printf("Type world name:");
	std::getline(std::cin, worldInfo.name);

	printf("Type world width:");
	std::cin >> width;

	printf("And world heigth:");
	std::cin >> heigth;

	world.setSize(width, heigth);

	std::string line;
	
	printf("\nType seed (default: %d): ", seed);

	std::getline(std::cin, line);
	std::getline(std::cin, line);
	if (!line.empty()) {
		std::stringstream(line) >> seed;
	}
	Random::setSeed(seed);
	worldInfo.seed = seed;


	generateWorld();

	currentState = GUIState::PLAY;
	
}

void Simulation::drawSelectSaved(std::vector<WorldMeta>& worldInfo)
{
	system("cls");
	drawInfo();
	if (worldInfo.size() == 0) {
		printf("Couldn't find any save...\n");
		return;
	}
	int no = 0;
	
	printf("*=================\n");
	printf("| Your Saves\n");
	for (auto& x : worldInfo) {
		printf("|%d) %s	seed: %u\n",no, x.name.c_str(), x.seed);
		no++;
	}
	printf("|%zd: GO BACK\n", worldInfo.size());
	printf("*=================\n");

}

void Simulation::showGUI()
{
	
	currentState = GUIState::MAIN;
	char input;

	//Using a state machine concept for menu.
	while (currentState != EXIT) {
		switch (currentState)
		{
		case MAIN:
		{
			handleMenu();
		}
		break;
		case LOAD:
			handleLoad();
			break;
		case NEW:
			handleNewGame();
			break;
		case PLAY:
			system("cls");
			printf("Welcome to the simulation\n");
			play();
			break;
		}

	}
	


}

void Simulation::play()
{
	system("cls");

	drawInfo();
	//in first frame all animals are being added to game
	world.updateExecuteOrder();
	world.drawWorld();

	//after a that we can begin a simulation
	while (true) {
		Input::getKey();
		system("cls");
		drawInfo();

		if (Input::isKeyPressed('q')) {
			currentState = MAIN;
			world.clear();
			break;
		}
		if (Input::isKeyPressed('s')) {
			saveSimulation();
			printf("Simulation Saved!\n");
			world.drawWorld();
			continue;
		}

		world.updateWorld();
		world.drawWorld();
	}
}

void Simulation::generateWorld()
{

	world.initialize();

	std::vector<GridVector> freeSpots;
	std::vector<int> organismIDs;
	GridVector size = world.getSize();

	for (int x = 0; x < size.x; x++) {
		for (int y = 0; y < size.y; y++) {
			freeSpots.push_back(GridVector(x, y));
		}
	}

	int animalCount = OrganismFactory::AnimalName::ANIMAL_COUNT;
	int plantCount = OrganismFactory::PlantName::PLANT_COUNT;
	int maxOrganismCopies = (size.x * size.y) / (plantCount + animalCount);
	maxOrganismCopies = (maxOrganismCopies > 2) ? maxOrganismCopies - 1 : maxOrganismCopies;
	if (maxOrganismCopies > 4) {
		maxOrganismCopies = 4;
	}
	if (maxOrganismCopies < 2) {
		printf("The area isn't enought for at least 2 representant of each species\n");
		printf("Be aware that not all animals will participate in simulation\n");
	}

	for (int i = 0; i < animalCount + plantCount; i++) {
		organismIDs.push_back(i);
	}

	//we add human at the beginning
	//And yes animals were on Earth before human, but i don't care
	{
		auto it = freeSpots.begin() + Random::number(freeSpots.size());
		Human* human = new Human(world, *it);
		human->addSkill(HumanSkillFactory::HumanSkillName::ALZURE_SHIELD);
		world.addOrganism(human);
		freeSpots.erase(it);
	}

	printf("Generating world...");

	int count;
	int id;
	for (int i = 0; i < animalCount + plantCount; i++) {


		auto organismIt = organismIDs.begin() + Random::number(organismIDs.size());
		id = *organismIt;

		count = Random::number(2, maxOrganismCopies);
		for (int i = 0; i < count; i++) {
			if (freeSpots.size() == 0) break;
			auto it = freeSpots.begin() + Random::number(freeSpots.size());
			
			world.addOrganism(organismFactory.createOrganism(id, *it));

			freeSpots.erase(it);
		}

		organismIDs.erase(organismIt);
	}

}

void Simulation::saveSimulation()
{
	std::vector<WorldMeta> saves;
	//Open metafile
	bool isCorrupted = readSaveInfo(saves);

	//read all info, if there is already world with same name, override it

	bool overwrite = false;
	for (auto& x : saves) {
		if (x.name == worldInfo.name) {
			overwrite = true;
		}
	}

	if (!overwrite) {
		saves.push_back(worldInfo);
	}

	writeSaveInfo(saves);
	writeWorldSave();

}

void Simulation::readSimulation(WorldMeta info)
{
	std::string path = "data/" + info.name + ".save";
	worldInfo = info;

	try {
		readWorld(path);
	}
	catch (const LoadExeption& e) {
		throw;
	}
}
