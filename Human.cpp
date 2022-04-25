#include "Human.h"

void Human::handleInput()
{
    if (Input::isKeyPressed(CharacterControls::SKILL)) {
        activateSkill(0);
    }

    if (Input::isKeyPressed(CharacterControls::DOWN_ARROW, true)) {
        moveDirection = GridVector(0, 1);
    }
    else if (Input::isKeyPressed(CharacterControls::UP_ARROW, true)) {
        moveDirection = GridVector(0, -1);
    }
    else if (Input::isKeyPressed(CharacterControls::LEFT_ARROW, true)) {
        moveDirection = GridVector(-1,0);
    }
    else if (Input::isKeyPressed(CharacterControls::RIGHT_ARROW, true)) {
        moveDirection = GridVector(1,0);
    }
    else {
        moveDirection = GridVector(0, 0);
    }

}


void Human::activateSkill(int number)
{
    if (skills.size() < number || skills.size() == 0) {
        printf("No binded skill at given slot\n");
        return;
    }
    skills[number]->activate();
}

void Human::addSkill(HumanSkill& newSkill)
{
    skills.push_back(&newSkill);
}

void Human::addSkill(int skillID)
{
    HumanSkill* skill = skillFactory.createSkill(skillID);
    addSkill(*skill);
}

std::string Human::toString()
{
    return std::string();
}

void Human::collision(Organism& other)
{
    for (auto* skill : skills) {
        if(skill->isActive())
            skill->handleCollision(other);
    }

    if (!isStuned()) {
        Animal::collision(other);
    }
}

void Human::action()
{
    handleInput();

    for (auto skill : skills) {
        skill->updateStatus();
        std::cout << skill->toString();
    }
    
    if (moveDirection == GridVector(0, 0)) return;

    if (world.isPositionValid(position + moveDirection)) {
        Animal::action(position + moveDirection);
    }
}

void Human::writeToFile(std::ofstream& file)
{
    Organism::writeToFile(file);
    file << " " << skills.size() << " ";
    for (auto skill : skills) {
        file << skillFactory.getSkillId(skill);
        skill->writeToFile(file);
    }
}

void Human::readFromFile(std::ifstream& file)
{
    Animal::readFromFile(file);
    int n_ofSkills;
    int skillId;
    file >> n_ofSkills;
    HumanSkill* currentSkill;

    for (int i = 0; i < n_ofSkills; i++) {
        file >> skillId;
        currentSkill = skillFactory.createSkill(skillId);
        if (currentSkill != nullptr) {
            currentSkill->readFromFile(file);
            addSkill(*currentSkill);
        }
        else {
            throw LoadExeption("Reading Save: Human: Save Record contain's unrecognized skill");
        }
    }

}

void Human::draw()
{
    printf("@");
}

Animal* Human::clone()
{
    return new Human(*this);
}
