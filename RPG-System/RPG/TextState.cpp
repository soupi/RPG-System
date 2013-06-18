#include "TextState.h"
#include "Controller.h"
#include "Bank.h"
#include "ParamsCtrl.h"

bool TextState::handleEvents(const Control& controls)
{
	if (controls.isPressed(ESC))
		_pop.set();

	return false;
}
void TextState::Update(Controller& ctrl, float elapsedTime)
{
	if (_pop)
		ctrl.getStateMachine().Pop();
}

void TextState::Render(Controller& ctrl)
{
	ctrl.getWindow().draw(_text);
}

void TextState::init(const string& str)
{
	_text.setFont(Bank<sf::Font>::getInstance().get("resources/consola.ttf"));
	_text.setString(str);
	_text.setOrigin(_text.getLocalBounds().width/2, _text.getLocalBounds().height/2); 
	_text.setCharacterSize(40);
}

void TextState::Enter(shared_ptr<StateParams>& params) { _text.setPosition(params->getCtrl().getView().getCenter()); }