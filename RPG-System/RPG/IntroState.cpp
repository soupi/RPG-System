#include "IntroState.h"
#include "Controller.h"
#include "ParamsCtrl.h"
#include "ParamsMap.h"
#include <memory>
#include <fstream>

using std::shared_ptr;


bool IntroState::handleEvents(const Control& controls)
{
	if (!_dialog->handleEvents(controls)) 
		_change_state.set(); // change state when dialog is finished

	return false;
}
void IntroState::Update(Controller& ctrl, float elapsedTime)
{
	if (_change_state) // change to starting map
		ctrl.getStateMachine().Change("localmap", shared_ptr<StateParams>(new ParamsMap(ctrl, _map_name, _starting_tile)));

	_dialog->Update(ctrl, elapsedTime); // updated dialog
}

void IntroState::Render(Controller& ctrl)
{
	_dialog->Render(ctrl);
}

void IntroState::init(shared_ptr<StateParams>& params)
{
	// open intro file
	std::ifstream introfile;
	introfile.open("resources/intro.txt");

	if (!introfile)
	{
		std::cerr << "Failed to open file: resources/intro.txt "<< std::endl;
		exit(EXIT_FAILURE);
	}
	// -------------
	// read introduction str
	string str;
	getline(introfile, str);
	_dialog = shared_ptr<Dialog>(new Dialog(str, sf::Color::Transparent, sf::Color::Transparent));
	_dialog->Enter(params->getCtrl().getHero());
	// read first map to show
	introfile >> _map_name >> _starting_tile;
}