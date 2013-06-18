#include "Help.h"
#include "Controller.h"
#include "Bank.h"

// handle events
bool Help::handleEvents(const Control& controls)
{
	if (controls.isPressed(ESC))
		_pop.set(); // set pop to go back if esc is pressed

	return false;
}
void Help::Update(Controller& ctrl, float elapsedTime)
{
	if (_pop.state()) // go back to previous state
		ctrl.getStateMachine().Pop();
}

void Help::Render(Controller& ctrl)
{
	ctrl.getWindow().draw(_key_layout);
}

// set help
void Help::init()
{
	_key_layout.setTexture(Bank<sf::Texture>::getInstance().get("resources/keyboardlayout.jpg"));
	_key_layout.setOrigin(_key_layout.getLocalBounds().width/2, _key_layout.getLocalBounds().height/2); 
}

// set position of help 
void Help::Enter(shared_ptr<StateParams>& params)
{
	_key_layout.setPosition(params->getCtrl().getView().getCenter());
}