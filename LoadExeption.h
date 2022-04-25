#pragma once
#include <exception>

class LoadExeption : public std::exception
{
public:
	LoadExeption(const char* msg) : std::exception(msg) {

	}

};

