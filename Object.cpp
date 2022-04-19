#include "Object.h"

std::string Object::getName()
{
	return name;
}

void Object::setName(std::string newName)
{
	name = newName;
}

bool Object::compare(Object* other)
{
	return typeid(*this) == typeid(*other);
}

bool Object::compare(Object& other)
{
	return typeid(*this) == typeid(other);
}
