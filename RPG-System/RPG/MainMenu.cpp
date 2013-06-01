#include "MainMenu.h"
#include "Controller.h"
#include "ParamsCtrl.h"
#include <memory>

using std::shared_ptr;

bool MainMenu::handleEvents(const Control& controls)
{

	if (controls.isPressed(MOUSE_PRIMARY))
		_change_state.set();
			
	else if (controls.isPressed(MOUSE_SECONDARY))
		_color += 79 % 255;	

	if (!_dialog.handleEvents(controls))
			_change_state.set();

	return false;
}
void MainMenu::Update(Controller& ctrl, float elapsedTime)
{
	if (_change_state)
		ctrl.getStateMachine().Change("localmap", shared_ptr<StateParams>(new ParamsMap(ctrl, "map.mp", 39)));

	_dialog.Update(ctrl, elapsedTime);

	_rect.setFillColor(sf::Color::Color(_color, 100, 100));
}

void MainMenu::Render(Controller& ctrl)
{
	ctrl.getWindow().draw(_rect);
	_dialog.Render(ctrl);
}

void MainMenu::init()
{
	_rect.setPosition(0.f,0.f);
	_rect.setSize(sf::Vector2f(800.f, 600.f));
	_rect.setFillColor(sf::Color::Red);
}