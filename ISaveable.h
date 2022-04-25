#pragma once
#include <fstream>
#include "LoadExeption.h"

class ISaveable
{
public:
	virtual void writeToFile(std::ofstream&) = 0;
	virtual void readFromFile(std::ifstream&) = 0;
};

