#pragma once

// stats for battles

#include <SFML/Graphics.hpp>

const unsigned BASE = 10;

class Stats 
{
public:
	Stats(unsigned atk = BASE, unsigned def = BASE, unsigned luck = BASE) : _ATK(atk), _DEF(def), _LUCK(luck) 
	{
		if (def == 0) // avoid division by zero in calc damage
			_DEF = 1;
	}
	unsigned ATK() const { return _ATK; }
	unsigned DEF() const { return _DEF; }
	unsigned LUCK() const { return _LUCK; }

	Stats Raise() 
	{
		Stats change(rand() % 10, rand() % 10, rand() % 5);
		_ATK += change.ATK();
		_DEF += change.DEF();
		_LUCK += change.LUCK();
		return change;
	}

private:
	unsigned _ATK;
	unsigned _DEF;
	unsigned _LUCK;
};

int calcDamage(Stats offense, Stats defense, int power);