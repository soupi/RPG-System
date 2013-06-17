#include "GameOverState.h"
#include "Controller.h"
#include "Bank.h"
#include "ParamsCtrl.h"

bool GameOver::handleEvents(const Control& controls)
{
	return (controls.isPressed(ENTER) || controls.isPressed(ESC));
}
void GameOver::Update(Controller& ctrl, float elapsedTime)
{

	_text.setPosition(ctrl.getView().getCenter());
}

void GameOver::Render(Controller& ctrl)
{
	ctrl.getWindow().draw(_text);
}

void GameOver::init()
{
	_text.setFont(Bank<sf::Font>::getInstance().get("resources/consola.ttf"));
	_text.setString("Game Over.");
	_text.setOrigin(_text.getLocalBounds().width/2, _text.getLocalBounds().height/2); 
	_text.setCharacterSize(50);
}