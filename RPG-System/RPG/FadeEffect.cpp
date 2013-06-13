#include "FadeEffect.h"
#include "Controller.h"

void Fade::fadeIn()
{
	_rect.setFillColor(sf::Color::Color(0,0,0,255));
	_fade_type = FADE_IN;
}
void Fade::fadeOut()
{
	_rect.setFillColor(sf::Color::Color(0,0,0,0));
	_fade_type = FADE_OUT;
}

void Fade::update(Controller& ctrl, float elapsedTime)
{
	unsigned a = _rect.getFillColor().a;

	if (_fade_type == FADE_OUT && unsigned(_rect.getFillColor().a) < 240)
		_rect.setFillColor(sf::Color::Color( 0, 0, 0, sf::Uint8(_rect.getFillColor().a + elapsedTime/1.2f * 255)));
	else if (_fade_type == FADE_IN && unsigned(_rect.getFillColor().a) > 10)
		_rect.setFillColor(sf::Color::Color( 0, 0, 0, sf::Uint8(_rect.getFillColor().a - elapsedTime/1.2f * 255)));
	else _fade_type = NONE;

	_rect.setSize(ctrl.getView().getSize());
	_rect.setPosition(ctrl.getView().getCenter());
	_rect.setOrigin(_rect.getSize().x/2.f, _rect.getSize().y/2.f);
}
void Fade::render(Controller& ctrl)
{
	ctrl.getWindow().draw(_rect);
}