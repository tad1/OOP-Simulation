#pragma once
#include <time.h>
#include <stdlib.h>

class Random {
private:

	size_t count;

	Random() {
		count = 0;
		srand(time(NULL));
	};


	int INumber(int limit, int start = 0) {
		return (IRandi() % limit) + start;
	}

	//returns true in amount/total% cases
	bool IChance(int amount, int total = 100) {
		return (IRandi() % total) + 1 < amount;
	}

	void ISetSeed(unsigned int seed) {
		count = 0;
		srand(seed);
	}

	int IRandi() {
		count++;
		return rand();
	}

public:

	/// <returns>Singleton instance</returns>
	static Random& get() {
		static Random instance;
		return instance;
	}

	/// <returns>Exclusive Random number</returns>
	static int number(int limit) {
		return get().INumber(limit);
	}

	/// <returns>Exclusive Random number</returns>
	static int number(int start, int limit) {
		return get().INumber(limit, start);
	}

	static int chance(int amount, int total = 100) {
		return get().IChance(amount, total);
	}

	static int randi() {
		return get().IRandi();
	}

	static void setSeed(unsigned int seed) {
		get().ISetSeed(seed);
	}

	static unsigned int getCount() {
		return get().count;
	}

	//Prevents to copy instance
	Random(const Random&) = delete;
};