#pragma once

// game over state will be called when the game is over. the program will exit when you press ESC or ENTER

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"

class TextState : public State
{
public:
	TextState(const string& str) { init(str); }
	virtual ~TextState() { }
	virtual void Enter(shared_ptr<StateParams>& params);
	virtual void Exit() { }
	virtual bool handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(Controller& ctrl);

protected:
	sf::Text _text;
	Flag _pop;
private:
	virtual void init(const string& str);

};