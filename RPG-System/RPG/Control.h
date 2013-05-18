#pragma once

#include <SFML\Graphics.hpp>

enum CONTROL {
	USE = 0,
	UP = 1,
	DOWN = 2,
	RIGHT = 3,
	LEFT = 4,
	PRIMARY = 5,
	SECONDARY = 6,
	PAUSE = 7,
	MOUSE_PRIMARY = 8,
	MOUSE_SECONDARY = 9

};

const unsigned NUM_OF_CONTROLS = 10;


class Control
{
public:
	Control();
	Control(bool controls[NUM_OF_CONTROLS]);
	bool isPressed(CONTROL control) const;


private:
	bool _controls_pressed[NUM_OF_CONTROLS];
};