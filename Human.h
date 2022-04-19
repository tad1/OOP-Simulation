#pragma once
#include "Animal.h"
#include "HumanSkill.h"
#include "AlzureShieldSkill.h"



class Human :
    public Animal
{


private:
    friend class AlzureShieldSkill;
protected:

    GridVector moveDirection;
    std::vector<HumanSkill*> skills;

public:

    static const struct CharacterControls {
        static const char UP_ARROW = 72;
        static const char DOWN_ARROW = 80;
        static const char LEFT_ARROW = 75;
        static const char RIGHT_ARROW = 77;
        static const char SKILL = 49;
    };

	Human(World& world, GridVector position) : Animal(world, position, 4, 5)  {
		name = "Human";
        moveDirection = GridVector(0, 0);
        
        skills.push_back(new AlzureShieldSkill(*this));
	};

    ~Human() {
        for (auto* x : skills) {
            delete x;
        }
    }
    void setDirection(GridVector);
    void activateSkill(int number);
    void addSkill(HumanSkill&);

    // Odziedziczono za poœrednictwem elementu Animal
    virtual std::string toString() override;
    virtual std::string toJSON() override;

    virtual void collision(Organism& other) override;
    virtual void action() override;
    
    virtual void draw() override;

    virtual Animal* clone() override;

};

