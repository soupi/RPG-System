#include "Splash.h"
#include "Bank.h"
#include "ChangeMap.h"
#include "Controller.h"


// init splash
void Splash::init()
{
	// get logo
	_logo.setTexture(Bank<sf::Texture>::getInstance().get("resources/logo.png"));
	_logo.setOrigin(_logo.getTextureRect().width/2.f, _logo.getTextureRect().height/2.f);
	_rect.setFillColor(sf::Color::White); // background

	// load shader
	_shader.loadFromFile("resources/wave.vert", sf::Shader::Vertex);
	_shade_timer = 0.f;
	
}

// update the splash state
void Splash::Update(Controller& ctrl, float elapsedTime)
{
	// set logo on window
	_logo.setPosition(ctrl.getView().getCenter());
	_rect.setPosition(_logo.getPosition().x,0);
	_rect.setSize(ctrl.getView().getSize());
	_rect.setPosition(_logo.getPosition().x - _rect.getSize().x/2, _logo.getPosition().y - _rect.getSize().y/2);

	// change animation (I don't know what I'm doing lol.)
	_shade_timer += elapsedTime;
	if (1.f < _shade_timer && _shade_timer < 4.17f)
	{
		_shader.setParameter("wave_phase", elapsedTime);
		_shader.setParameter("wave_amplitude", tan(_timer-1) * 50, sin(_shade_timer-1) * 40);
	}
	// stop animation and start fading
	else if (4.67f < _shade_timer)
	{
		if (!_fading) // if still not fading, set fade mode
		{
			_fading = true;
			_fade.fadeOut();
		}
		else // if fading, update fade
			_fade.update(ctrl, elapsedTime);
	}

	_timer += elapsedTime;
	if (_fading && !_fade.isFading() || _esc) // continue until fading has stopped or the user pressed ESC
	{
		shared_ptr<StateParams> params( new ParamsCtrl(ctrl));
		ctrl.getStateMachine().Change("mainmenu", params); // switch to main menu
	}

}

// render splash
void Splash::Render(Controller& ctrl)
{
	ctrl.getWindow().draw(_rect);
	ctrl.getWindow().draw(_logo, &_shader);

	if (_fading)
		_fade.render(ctrl);
}

// handle events
bool Splash::handleEvents(const Control& controls)
{
	_esc = controls.isPressed(ESC);
	return false;
}