#pragma once

// splash screen state. will display the company's logo with animation.

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"
#include "Macros.h"
#include "FadeEffect.h"

class Splash : public State
{
public:
	Splash() : _timer(0.f), _fading(false), _esc(false) { init(); }
	virtual void Enter(shared_ptr<StateParams>& params) { _shade_timer = 0.f; _timer = 0.f; }
	virtual void Exit() { }
	virtual bool handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(Controller& ctrl);

private:
	sf::Sprite _logo;
	sf::RectangleShape _rect; // background
	float _timer;
	float _shade_timer;
	sf::Shader _shader; // for animation
	
	Fade _fade;
	bool _fading;

	bool _esc; // has esc been pressed?

	void init();
	
};