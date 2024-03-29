﻿#include "World.h"
#include "OrganismFactory.h"
#include <fstream>
#include <sstream>

World::World()
{
    map = nullptr;
}

World::World(GridVector size)
{
    mapSize = size;
    int arraySize = size.x * size.y;
    map = nullptr;

}

void World::setSize(int x, int y)
{
    mapSize = GridVector(x, y);
    int arraySize = x * y;
}

GridVector World::getSize()
{
    return mapSize;
}

void World::initialize()
{
    clear();

    if (mapSize.x <= 0) {
        mapSize.x = 20;
    }
    if (mapSize.y <= 0) {
        mapSize.y = 0;
    }
    int arraySize = mapSize.x * mapSize.y;
    map = new std::weak_ptr<Organism>[arraySize];
}

void World::clear()
{
    if (map != nullptr) {
        delete[] map;
        map = nullptr;
    }

    organismsToActivate.clear();

    for (auto& x : executeQueue) {
        x.second.clear();
    }
    executeQueue.clear();

    organisms.clear();
}

void World::drawWorld()
{
    GridVector currentPos(0, 0);
    std::weak_ptr<Organism> current;

    //Using this bad looking idea to ensure that the border is correctly displayed on Windows OS.
    // Note: on Linux, and Mac OS, we don't need this dirty trick
    //Defining Extended ASCII characters
    //                        ║            ╗                   ╝
    static unsigned char vertical = 186, upperRight = 187, bottomRight = 188;

    //                       ═                   ╔               ╚
    static unsigned char horizontal = 205, upperLeft = 201, bottomLeft = 200;
    

    printf("%c",upperLeft);
    for (int i = 0; i < mapSize.x; i++) {
        printf("%c",horizontal);
    }
    printf("%c\n",upperRight);


    for (; currentPos.y < mapSize.y; currentPos.y++) {
        std::cout << vertical;
        for (; currentPos.x < mapSize.x; currentPos.x++) {
            current = map[getIndexFromPosition(currentPos)];
            if (!current.expired()) {
                //pointer is valid
                auto organism = current.lock();
                organism->draw();
            }
            else {
                std::cout << " ";
            }
        }
        printf("%c",vertical);
        currentPos.x = 0;
        std::cout << "\n";
    }

    printf("%c",bottomLeft);
    for (int i = 0; i < mapSize.x; i++) {
        printf("%c",horizontal);
    }
    printf("%c\n",bottomRight);

}

void World::updateWorld()
{
    updateExecuteOrder();
    //Runs through execution queue set and execute on each organism action
    for(auto x = executeQueue.rbegin(); x != executeQueue.rend(); x++){
        for (auto it = x->second.begin(); it != x->second.end(); it++) {
            auto organism = it->lock();
            if (organism) {
                std::cout << organism->toString();
                organism->action();
            }
        }
    }
    printf("\n");
}

void World::addOrganism(Organism* organism)
{
    std::shared_ptr<Organism> sp(organism);
    organisms.push_back(sp);
    std::weak_ptr<Organism> wp = sp;

    //add it to map
    map[getIndexFromPosition(organism->getPosition())] = wp;
    
    //add to execute order    
    organismsToActivate.push_back(wp);

}

void World::removeOrganism(Organism* organism_p)
{
    for (auto it = organisms.begin(); it != organisms.end();) {
        if (it->get() == organism_p) {
            it->reset();
            organisms.erase(it);
            break;
        }
        else {
            it++;
        }
    }

}

void World::moveOrganism(GridVector source, GridVector destination)
{
    if (source == destination) return;
    if (isPositionValid(source) && isPositionValid(destination)) {
        map[getIndexFromPosition(destination)] = map[getIndexFromPosition(source)];
        map[getIndexFromPosition(source)] = std::weak_ptr<Organism>();
    }
}

void World::getNeighbourFields(GridVector position, std::vector<GridVector>& vector, int range)
{   
    vector.clear();
    GridVector newPos = position;
    for (newPos.x = position.x - range; newPos.x <= position.x + range; newPos.x++) {
        for (newPos.y = position.y - range; newPos.y <= position.y + range; newPos.y++) {
            if (isPositionValid(newPos) && position != newPos) {
                vector.push_back(GridVector(newPos));
            }
        }
    }
}

void World::getFreeNeighbourFields(GridVector position, std::vector<GridVector>& vector, int range)
{
    vector.clear();
    GridVector newPos = position;
    for (newPos.x = position.x - range; newPos.x <= position.x + range; newPos.x++) {
        for (newPos.y = position.y - range; newPos.y <= position.y + range; newPos.y++) {
            if (isPositionValid(newPos) && !isOrganismAtPosition(newPos)) {
                vector.push_back(GridVector(newPos));
            }
        }
    }
}

bool World::isOrganismAtPosition(GridVector pos)
{
    return !getFromMap(pos).expired();
}

std::weak_ptr<Organism> World::getFromMap(GridVector pos)
{
    if (!isPositionValid(pos)) return std::weak_ptr<Organism>();
    return map[getIndexFromPosition(pos)];
}

void World::saveWorldStateToFile(std::ofstream& file, OrganismFactory factory)
{
    //write size
    file << mapSize.x << " " << mapSize.y << std::endl;

    //write all organisms
    for (auto& x : executeQueue) {
        for (auto& y : x.second) {
            auto sp = y.lock();
            if (sp) {
                file << factory.getOrganismType(sp.get()) << " ";
                (*sp).writeToFile(file);
                file << std::endl;

            }
        }
    }
}

void World::loadWorldStateFromFile(std::ifstream & file, OrganismFactory organismFactory)
{
    GridVector newSize;
    //get size
    file >> newSize.x;
    file >> newSize.y;
    //initialize
    setSize(newSize.x, newSize.y);
    initialize();

    //load organisms
    std::string line;
    int type;
    GridVector pos;
    Organism* organism;

    //Allows to store current position of file
    std::streampos readPos = file.tellg();

    while (std::getline(file, line)) {
        //we use getline to determine if it isn't an end of file
        //we need to restore stream position.
        file.seekg(readPos);

        file >> type;
        file >> pos.x;
        file >> pos.y;

        organism = organismFactory.createOrganism(type, pos);


        if (organism) {
            //we restore file position to read correctly animal
            file.seekg(readPos);
            organism->readFromFile(file);
            addOrganism(organism);
        }

        readPos = file.tellg();

    }
}

inline bool World::isPositionValid(GridVector pos)
{
    return (pos.x >= 0 && pos.x < mapSize.x) && (pos.y >= 0 && pos.y < mapSize.y);
}

void World::updateExecuteOrder()
{
    for (auto& x : organismsToActivate) {
        addToExecuteOrder(x);
    }
    organismsToActivate.clear();
    
    //We use here an interesting solution for deleting elements, while iteration throught container.
    for (auto& x : executeQueue) {
        for (auto it = x.second.begin(); it != x.second.end();) {
            if (it->expired()) {
                it = x.second.erase(it); //an erase function returns a next element.
                //but when iterator is deleted without moving to the next element in this way,
                //it result in unpredictable bechaviour.
            }
            else {
                it++;
            }
        }
    }
    
}

void World::addToExecuteOrder(std::weak_ptr<Organism> organism)
{
    if (organism.expired()) return;

    int initiative = organism.lock()->getInitiative();
    auto key = executeQueue.find(initiative);
    if (key != executeQueue.end()) {

        key->second.push_back(organism);
    }
    else {
        addExecutionQueueToMap(initiative);
        executeQueue.find(initiative)->second.push_back(organism);
    }
}

int World::getIndexFromPosition(GridVector pos) const
{
    return pos.y * mapSize.x + pos.x;
}

void World::addExecutionQueueToMap(int key)
{
    executeQueue.emplace(key, organismQueue());
}
