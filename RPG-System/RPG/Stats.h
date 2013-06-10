#pragma once

#include <SFML/Graphics.hpp>

class Stats 
{
public:
	Stats(unsigned atk = 10, unsigned def = 10, unsigned luck = 10) : _ATK(atk), _DEF(def), _LUCK(luck) 
	{
		if (def == 0)
			_DEF = 1;
	}
	unsigned ATK() const { return _ATK; }
	unsigned DEF() const { return _DEF; }
	unsigned LUCK() const { return _LUCK; }

	Stats Raise() 
	{
		Stats change(rand() % 3, rand() % 3, rand() % 2);
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