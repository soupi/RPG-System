#include "Pause.h"
#include "Controller.h"
#include "Bank.h"
#include "ParamsCtrl.h"
#include "menu/Commands.h"

bool Pause::handleEvents(const Control& controls)
{
	if (controls.isPressed(A) || controls.isPressed(ENTER))
		_menu->execute();
	
	if (controls.isPressed(DOWN))
		_menu->markNext();
	else if (controls.isPressed(UP))
		_menu->markPrev();

	return _escape;
}
void Pause::Update(Controller& ctrl, float elapsedTime)
{


}

void Pause::Render(Controller& ctrl)
{
	_menu->display(ctrl.getWindow());
}

void Pause::init(shared_ptr<StateParams>& params)
{
	_escape = false;

	_menu = shared_ptr<Menu>(new Menu(params->getCtrl().getView().getCenter()*sf::Vector2f(0.918f,1), sf::Vector2f(200,200), 60));
	_menu->add("Unpause", new PopState(params->getCtrl().getStateMachine()));
	_menu->add("Help", new RunHelp(params->getCtrl().getStateMachine(), params));
	_menu->add("Exit", new PauseEscape(*this));
}