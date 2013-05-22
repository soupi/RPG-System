#pragma once

class Stats 
{
public:
	Stats(unsigned atk = 10, unsigned def = 10, unsigned luck = 10) : _ATK(atk), _DEF(def), _LUCK(luck) { }
	unsigned ATK() { return _ATK; }
	unsigned DEF() { return _DEF; }
	unsigned LUCK() { return _LUCK; }

private:
	unsigned _ATK;
	unsigned _DEF;
	unsigned _LUCK;
};