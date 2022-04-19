// OOP-Simulation.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <conio.h>
#include "World.h"
#include "Sheep.h"
#include "Wolf.h"
#include "Fox.h"
#include "Turtle.h"
#include "Dandelion.h"
#include "Grass.h"
#include "Guarana.h"
#include "Wolfberries.h"
#include "PineBorscht.h"
#include "Antelope.h"
#include "Human.h"
#include "Simulation.h"

int main()
{
	Simulation sim;
	sim.showGUI();
	return 0;





#if 0
	char input;
	while (true)
	{
		if (_kbhit()) {
			input = _getch();

			system("cls");
			if (input == 'q') {
				break;
			}

			if (input == -32) {
				input = _getch();

				switch (input)
				{
				case Human::CharacterControls::UP_ARROW:
					character->setDirection(GridVector(0, -1));
					break;
				case Human::CharacterControls::DOWN_ARROW:
					character->setDirection(GridVector(0, 1));
					break;
				case Human::CharacterControls::LEFT_ARROW:
					character->setDirection(GridVector(-1, 0));
					break;
				case Human::CharacterControls::RIGHT_ARROW:
					character->setDirection(GridVector(1, 0));
					break;

				default:
					break;
				}
			}
			else if (input == Human::CharacterControls::SKILL) {
				character->activateSkill(0);
			}

			world.updateWorld();
			world.drawWorld();
			std::cout << "done";
		}
	}
#endif // 0

   
}
