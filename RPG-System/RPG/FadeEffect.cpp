#include "FadeEffect.h"
#include "Controller.h"

void Fade::fadeIn()
{
	_rect.setFillColor(sf::Color::Color(0,0,0,255));
	_alpha = 255;
	_fade_type = FADE_IN;
}
void Fade::fadeOut()
{
	_rect.setFillColor(sf::Color::Color(0,0,0,0));
	_alpha = 0;
	_fade_type = FADE_OUT;
}

void Fade::update(Controller& ctrl, float elapsedTime)
{
	if (_fade_type == FADE_OUT && _alpha < 255)
	{
		_alpha += int(elapsedTime/1.2f * 255);
		if (_alpha > 255)
			_alpha = 255;
		_rect.setFillColor(sf::Color::Color( 0, 0, 0, _alpha));
	}

	else if (_fade_type == FADE_IN && 0 < _alpha)
	{
		_alpha -= int(elapsedTime/1.2f * 255);
		if (_alpha < 0)
			_alpha = 0;
		_rect.setFillColor(sf::Color::Color( 0, 0, 0, _alpha));
	}
	else _fade_type = NONE;

	_rect.setSize(ctrl.getView().getSize());
	_rect.setPosition(ctrl.getView().getCenter());
	_rect.setOrigin(_rect.getSize().x/2.f, _rect.getSize().y/2.f);
}
void Fade::render(Controller& ctrl)
{
	ctrl.getWindow().draw(_rect);
}