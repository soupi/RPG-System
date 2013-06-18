#include "ScrolledUpTextState.h"
#include "Bank.h"
#include "Controller.h"


void ScrolledUpTextState::Update(Controller& ctrl, float elapsedTime)
{
	TextState::Update(ctrl, elapsedTime);

	if (_text.getPosition().y > ctrl.getView().getCenter().y)
		_text.setPosition(_text.getPosition().x, _text.getPosition().y - elapsedTime * DEFAULT_SPEED);
}

void ScrolledUpTextState::Enter(shared_ptr<StateParams>& params) 
{ 
	_text.setPosition(params->getCtrl().getView().getCenter().x, 
		params->getCtrl().getView().getCenter().y + params->getCtrl().getView().getSize().y/2); 
}