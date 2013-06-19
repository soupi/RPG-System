#include "EndingScript.h"
#include "Controller.h"
#include "ParamsCtrl.h"
#include "ScrolledUpTextState.h"
#include <algorithm>

EndingScript::EndingScript(string& text)
{
	std::replace(text.begin(), text.end(), ';', '\n'); // break long line to paragraph
	_text = text;
}

bool EndingScript::Update(Controller& ctrl, float elapsedTime)
{
	// fade out of current map
	if (_fade.isFading())
		_fade.update(ctrl, elapsedTime);
	
	else { // if we are done fading, add end sequence and change to it.
		ctrl.getStateMachine().Add("end", shared_ptr<State>(new ScrolledUpTextState(_text)));
		ctrl.getStateMachine().Change("end", shared_ptr<StateParams>(new ParamsCtrl(ctrl)));
		_continue = false;
	}
	return _continue;
}