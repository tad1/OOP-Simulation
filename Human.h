#pragma once
#include "Animal.h"
#include "HumanSkill.h"
#include "AlzureShieldSkill.h"
#include "HumanSkillFactory.h"
#include "Input.h"
#include <fstream>



class Human :
    public Animal
{
private:
    //A friend keyword, allows us to remove definitions of skills in Human class and define it in a speparate file.
    friend class AlzureShieldSkill;

    void handleInput();

protected:
    GridVector moveDirection;

    //Instead of making hard typed skill in human class. I decided to create a composition based solution.
    //By saying "composition base" I mean making a human class more universal, by adding a composition layer over inheritance.
    std::vector<HumanSkill*> skills;
    HumanSkillFactory skillFactory;

public:

    //A hard typed controlls, due the lack of proper input handler (for keyboard keys) for standard C++.
    static const struct CharacterControls {
        static const int UP_ARROW = 72;
        static const int DOWN_ARROW = 80;
        static const int LEFT_ARROW = 75;
        static const int RIGHT_ARROW = 77;
        static const int SKILL = 49;
    };

	Human(World& world, GridVector position) : Animal(world, position, 4, 5), skillFactory(*this) {
		name = "Human";
        moveDirection = GridVector(0, 0);
	};

    ~Human() {
        for (auto* x : skills) {
            delete x;
        }
    }
    
    void activateSkill(int number);
    void addSkill(HumanSkill&);
    void addSkill(int);

    // Odziedziczono za poœrednictwem elementu Animal
    virtual std::string toString() override;

    virtual void collision(Organism& other) override;
    virtual void action() override;
    
    virtual void writeToFile(std::ofstream&) override;
    virtual void readFromFile(std::ifstream&) override;

    virtual void draw() override;
    virtual Animal* clone() override;

};

