#include "TextState.h"
#include "Controller.h"
#include "Bank.h"
#include "ParamsCtrl.h"

// if ESC is pressed, set pop
bool TextState::handleEvents(const Control& controls)
{
	if (controls.isPressed(ESC))
		_pop.set();

	return false;
}
// if pop is set, pop the state
void TextState::Update(Controller& ctrl, float elapsedTime)
{
	if (_pop)
		ctrl.getStateMachine().Pop();
}

void TextState::Render(Controller& ctrl)
{
	ctrl.getWindow().draw(_text);
}

// set text
void TextState::init(const string& str)
{
	_text.setFont(Bank<sf::Font>::getInstance().get("resources/consola.ttf"));
	_text.setString(str);
	_text.setOrigin(_text.getLocalBounds().width/2, _text.getLocalBounds().height/2); 
	_text.setCharacterSize(40);
}
// set text position
void TextState::Enter(shared_ptr<StateParams>& params) { _text.setPosition(params->getCtrl().getView().getCenter()); }