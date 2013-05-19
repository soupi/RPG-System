#include "Control.h"

Control::Control()
{
	for (unsigned i = 0; i < NUM_OF_CONTROLS; ++i)
		_controls_pressed[i] = false;
}

Control::Control(bool controls[NUM_OF_CONTROLS])
{
	for (unsigned i = 0; i < NUM_OF_CONTROLS; ++i)
		_controls_pressed[i] = controls[i];
}

void Control::setControls(bool controls[NUM_OF_CONTROLS])
{
	for (unsigned i = 0; i < NUM_OF_CONTROLS; ++i)
		_controls_pressed[i] = controls[i];
}

bool Control::isPressed(CONTROL control) const
{
	return _controls_pressed[control];
}