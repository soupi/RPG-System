#include "Control.h"

// default constructor. sets everything to false
Control::Control()
{
	for (unsigned i = 0; i < NUM_OF_CONTROLS; ++i)
		_controls_pressed[i] = false;
}

// Constructor that gets the stats of the controls
Control::Control(bool controls[NUM_OF_CONTROLS])
{
	for (unsigned i = 0; i < NUM_OF_CONTROLS; ++i)
		_controls_pressed[i] = controls[i];
}

// sets controls
void Control::setControls(bool controls[NUM_OF_CONTROLS])
{
	for (unsigned i = 0; i < NUM_OF_CONTROLS; ++i)
		_controls_pressed[i] = controls[i];
}
// returns if a certain control is pressed
bool Control::isPressed(CONTROL control) const
{
	return _controls_pressed[control];
}