#include "MainMenu.h"
#include "Controller.h"
#include "ParamsCtrl.h"
#include "ParamsMap.h"
#include <memory>
#include "menu/Commands.h"

using std::shared_ptr;

bool MainMenu::handleEvents(const Control& controls)
{			
	if (controls.isPressed(A) || controls.isPressed(ENTER))
		_menu->execute();
	
	if (controls.isPressed(DOWN))
		_menu->markNext();
	else if (controls.isPressed(UP))
		_menu->markPrev();

	return false;
}
void MainMenu::Update(Controller& ctrl, float elapsedTime)
{

}

void MainMenu::Render(Controller& ctrl)
{
	_menu->display(ctrl.getWindow());
}

void MainMenu::init(shared_ptr<StateParams>& params)
{
	_menu = shared_ptr<Menu>(new Menu(params->getCtrl().getView().getCenter()*sf::Vector2f(0.918f,1), sf::Vector2f(200,200), 60));
	_menu->add("Start Game", new StartGame(params->getCtrl().getStateMachine(), params));
	_menu->add("Help", new RunHelp(params->getCtrl().getStateMachine(), params));
	_menu->add("Credits", new RunCredits(params->getCtrl().getStateMachine(), params));
}