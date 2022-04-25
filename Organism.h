#pragma once
#include "Object.h"
#include "Vector2D.h"
#include "Random.h"
#include "ISaveable.h"

#include <iostream>

class World;

class Organism : public Object, public ISaveable
{
protected:
	bool alive;

	int strength;
	int initiative;
	GridVector position;
	World& world;

	void setPosition(GridVector);

public:
	Organism(World&, GridVector);
	Organism(World&, GridVector, int initiative, int strenght);

	void kill();
	bool isAlive();

	// Defines bechaviour of organism during the round
	virtual void action() = 0;
	// Defines bechaviour during the contact/collision with different organism
	virtual void collision(Organism&) = 0;
	// Draw organism graphical representation
	virtual void draw() = 0;
	virtual Organism* clone() = 0;

	virtual ~Organism() {
	};
	
	void setParamters(int newStrength, int newInitiative) {
		strength = newStrength;
		initiative = newInitiative;
	}
	
	int getInitiative() const{
		return initiative;
	}

	int getStrength() const{
		return strength;
	}

	GridVector getPosition() const{
		return position;
	}

	// Odziedziczono za poœrednictwem elementu ISaveable
	virtual void writeToFile(std::ofstream&) override;
	virtual void readFromFile(std::ifstream&) override;
};

