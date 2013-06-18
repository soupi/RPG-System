#include "FadeEffect.h"
#include "Controller.h"

// set fade mode to fade -in-
void Fade::fadeIn()
{
	_rect.setFillColor(sf::Color::Color(0,0,0,255));
	_alpha = 255; // black
	_fade_type = FADE_IN; // mode 
}
// set fade mode to fade -out-
void Fade::fadeOut()
{
	_rect.setFillColor(sf::Color::Color(0,0,0,0));
	_alpha = 0; // transperent
	_fade_type = FADE_OUT;
}

// update fade (change alpha)
void Fade::update(Controller& ctrl, float elapsedTime)
{
	// fade out until black
	if (_fade_type == FADE_OUT && _alpha < 255)
	{
		_alpha += int(elapsedTime/1.2f * 255);
		if (_alpha > 255)
			_alpha = 255;
		_rect.setFillColor(sf::Color::Color( 0, 0, 0, _alpha));
	}
	// or fade in until transperent
	else if (_fade_type == FADE_IN && 0 < _alpha)
	{
		_alpha -= int(elapsedTime/1.2f * 255);
		if (_alpha < 0)
			_alpha = 0;
		_rect.setFillColor(sf::Color::Color( 0, 0, 0, _alpha));
	}
	else _fade_type = NONE; // or set that there is no fade right now

	// center the rectangle
	_rect.setSize(ctrl.getView().getSize());
	_rect.setPosition(ctrl.getView().getCenter());
	_rect.setOrigin(_rect.getSize().x/2.f, _rect.getSize().y/2.f);
}
void Fade::render(Controller& ctrl)
{
	ctrl.getWindow().draw(_rect);
}