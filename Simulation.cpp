#include "Simulation.h"

bool Simulation::readSaveInfo(std::vector<WorldMeta>& saveInfo)
{
	saveInfo.clear();
	std::ifstream file("data/saveinfo.meta", std::ios::in);
	if (!file) {
		return true;
	}

	std::string line;
	std::string value;

	int counterMod = 2;
	int valueCounter = 0;
	WorldMeta currentInfo;
	while (std::getline(file, line)) {
		std::stringstream lstream(line);

		while (std::getline(lstream, value, ',')) {
			std::cout << "Value: " << value << "\n";
			switch (valueCounter)
			{
			case 0:
				currentInfo.name = value;
				break;
			case 1:
				//TODO: add check if value is number
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
		return true;
	}
	return 0;

}

void Simulation::writeSaveInfo(std::vector<WorldMeta>& saveInfo)
{
	std::ofstream file("data/saveinfo.meta", std::ios::out | std::ios::trunc);
	if (!file.is_open()) return;
	//TODO: make save working
	
	for (auto& info : saveInfo) {
		file << info.name << "," << info.seed << std::endl;
	}
	file.close();
}

void Simulation::readWorld(std::string path)
{
	std::ifstream file(path, std::ios::in);
	if (!file.is_open()) return;
	unsigned int seed;
	size_t count;
	
	file >> seed;
	file >> count;

	world.loadWorldStateFromFile(file, animalFactory);

	file.close();

}

void Simulation::writeWorldSave()
{
	std::string path = "data/" + worldInfo.name + ".save";
	std::ofstream file(path, std::ios::out | std::ios::trunc);
	if (!file.is_open()) return;

	file << worldInfo.seed <<" " << Random::getCount() << std::endl;

	//info about human

	//then we make a long loop for saving organisms
	world.saveWorldStateToFile(file, animalFactory);

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

	if (selectedWorld == saves.size()) {
		currentState = GUIState::MAIN;
	}
	else if (selectedWorld >= 0 && selectedWorld < saves.size()) {
		currentState = GUIState::PLAY;
		readSimulation(saves[selectedWorld]);
	}
	else {
		printf("Selected invalid save!\n");
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
	if (!line.empty()) {
		std::stringstream(line) >> seed;
	}
	std::cin >> seed;
	Random::setSeed(seed);
	worldInfo.seed = seed;


	generateWorld(seed);

	currentState = GUIState::PLAY;
	
}

void Simulation::drawSelectSaved(std::vector<WorldMeta>& worldInfo)
{
	drawInfo();
	if (worldInfo.size() == 0) {
		printf("Couldn't find any save...\n");
		return;
	}
	
	printf("|=================\n");
	printf("|Id		Seed\n");
	for (auto& x : worldInfo) {
		printf("|%s:	seed: %u\n", x.name.c_str(), x.seed);
	}
	printf("|%zd: GO BACK\n", worldInfo.size());
	printf("|=================\n");

}

void Simulation::showGUI()
{
	
	currentState = GUIState::MAIN;
	char input;

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
			printf("Welcome to the simulation");
			play();
			break;
		}

	}
	


}

void Simulation::play()
{
	drawInfo();
	char input;
	while (true) {
		input = _getch();
		system("cls");
		drawInfo();

		if (input == 'q') {
			currentState = MAIN;
			world.clear();
			break;
		}
		if (input == 's') {
			saveSimulation();
		}

		world.updateWorld();
		world.drawWorld();
	}
}

void Simulation::generateWorld(int seed)
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

	int animalCount = AnimalFactory::AnimalName::ANIMAL_COUNT;
	int plantCount = AnimalFactory::PlantName::PLANT_COUNT;
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

	//TODO: add human at the beginning
	//And yeah the animals were before human, but i don't care

	printf("Generating world...");

	std::random_shuffle(organismIDs.begin(), organismIDs.end());

	int count;
	int id;
	for (int i = 0; i < animalCount + plantCount; i++) {
		auto organismIt = organismIDs.begin() + Random::number(organismIDs.size());
		id = *organismIt;

		count = Random::number(maxOrganismCopies, 2);
		for (int i = 0; i < count; i++) {
			if (freeSpots.size() == 0) break;
			auto it = freeSpots.begin() + Random::number(freeSpots.size());
			
			if (id >= animalCount) {
				//adding a plant
				world.addOrganism(animalFactory.createPlant(id - animalCount, *it));
			}
			else {
				//adding an animal
				world.addOrganism(animalFactory.createAnimal(id, *it));
			}

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

	//read all info, if there is already world with same name and seed, override

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

	//if file is corrupted, or it doesn't exists create new
	//delete and save info file

	//next create a new file with simulation
}

void Simulation::readSimulation(WorldMeta info)
{
	std::string path = "data/" + info.name + ".save";
	Random::setSeed(info.seed);
	worldInfo = info;

	readWorld(path);
}
