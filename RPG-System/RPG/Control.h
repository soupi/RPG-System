#pragma once

#include <SFML\Graphics.hpp>

enum CONTROL {
	USE = 0,
	UP = 1,
	DOWN = 2,
	RIGHT = 3,
	LEFT = 4,
	A = 5,
	B = 6,
	C = 7,
	D = 8,
	PAUSE = 9,
	MOUSE_PRIMARY = 10,
	MOUSE_SECONDARY = 11

};

const unsigned NUM_OF_CONTROLS = 12;


class Control
{
public:
	Control();
	Control(bool controls[NUM_OF_CONTROLS]);
	void setControls(bool controls[NUM_OF_CONTROLS]);
	bool isPressed(CONTROL control) const;


private:
	bool _controls_pressed[NUM_OF_CONTROLS];
};