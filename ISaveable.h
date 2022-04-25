#pragma once
#include <fstream>
#include "LoadExeption.h"

//An interface for write and save functions.
class ISaveable
{
public:
	virtual void writeToFile(std::ofstream&) = 0;
	virtual void readFromFile(std::ifstream&) = 0;

};

