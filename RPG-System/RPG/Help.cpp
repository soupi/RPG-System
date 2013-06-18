#include "Help.h"
#include "Controller.h"
#include "Bank.h"

bool Help::handleEvents(const Control& controls)
{
	if (controls.isPressed(ESC))
		_pop.set();

	return false;
}
void Help::Update(Controller& ctrl, float elapsedTime)
{
	if (_pop.state())
		ctrl.getStateMachine().Pop();

	_key_layout.setPosition(ctrl.getView().getCenter());

}

void Help::Render(Controller& ctrl)
{
	ctrl.getWindow().draw(_key_layout);
}

void Help::init()
{
	_key_layout.setTexture(Bank<sf::Texture>::getInstance().get("resources/keyboardlayout.jpg"));
	_key_layout.setOrigin(_key_layout.getLocalBounds().width/2, _key_layout.getLocalBounds().height/2); 
}