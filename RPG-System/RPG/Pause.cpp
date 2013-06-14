#include "Pause.h"
#include "Controller.h"
#include "Bank.h"

bool Pause::handleEvents(const Control& controls)
{
	if (controls.isPressed(PAUSE))
		_change_state.set();

	return controls.isPressed(ESC);
}
void Pause::Update(Controller& ctrl, float elapsedTime)
{
	if (_change_state)
		ctrl.getStateMachine().Pop();

	_text.setPosition(ctrl.getView().getCenter());

}

void Pause::Render(Controller& ctrl)
{
	ctrl.getWindow().draw(_text);
}

void Pause::init()
{
	_text.setFont(Bank<sf::Font>::getInstance().get("resources/consola.ttf"));
	_text.setString("       PAUSE\n\nPRESS 'P' TO UNPAUSE\n  OR 'ESC' TO EXIT");
	_text.setOrigin(_text.getLocalBounds().width/2, _text.getLocalBounds().height/2); 
}