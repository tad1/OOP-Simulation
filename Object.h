#pragma once
#include <string>
#include <typeinfo>
class Object
{
protected:
	std::string name;
public:
	virtual std::string toString() = 0;
	std::string getName();
	void setName(std::string newName);
	virtual Object* clone() = 0;
	bool compare(Object*);
	bool compare(Object&);
	virtual ~Object() {};
};

