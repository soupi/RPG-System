#pragma once

// script to run to end the game.

#include "Script.h"
#include "FadeEffect.h"
#include <string>

using std::string;

class EndingScript : public Script
{
public:
	EndingScript(string& text);
	virtual bool handleEvents(const Control& controls) { return Continue(); }
	virtual bool Update(Controller&, float elapsedTime);
	virtual void Render(Controller& ctrl) { _fade.render(ctrl); }
private:
	string _text;
	Fade _fade;

	virtual void enter(Hero& hero) { hero.getHeroForMap()->stop(); _fade.fadeOut(); }
	virtual void exit() {}
};