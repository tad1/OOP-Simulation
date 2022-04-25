#pragma once
#include <conio.h>
#include <iostream>

//A singleton that wrap a conio.h style of input management.
class Input
{
	int keyPressed;
	bool isSpecial;
	
private:

	Input() {
		isSpecial = 0;
		keyPressed = 0;
	}

	int IGetKey() {
		keyPressed = _getch();
		if (keyPressed == 224) {
			isSpecial = true;
			keyPressed = _getch();
		}
		else {
			isSpecial = false;
		}
		return keyPressed;
	}

	bool IIsKeyPressed(int keyCode, bool special = false) {
		return keyPressed == keyCode && special == isSpecial;
	}


public:
	//A key function that makes all static functions, an singleton functions.
	static Input& get() {
		static Input instance;
		return instance;
	}

	static int getKey() {
		return get().IGetKey();
	}
	
	static bool isKeyPressed(int keyCode, bool special = false) {
		return get().IIsKeyPressed(keyCode, special);
	}
	
	//Prevents to copy instance
	Input(const Input&) = delete;

};

