#include "Splash.h"
#include "Bank.h"
#include "ChangeMap.h"
#include "Controller.h"

void Splash::init()
{
	_logo.setTexture(Bank<sf::Texture>::getInstance().get("resources/logo.png"));
	_logo.setOrigin(_logo.getTextureRect().width/2.f, _logo.getTextureRect().height/2.f);
	_rect.setFillColor(sf::Color::White);
	_shader.loadFromFile("resources/wave.vert", sf::Shader::Vertex);
	//_shader.loadFromFile("resources/wave.vert", "resources/pixelate.frag");
	_shade_timer = 0.f;
	
}

void Splash::Update(Controller& ctrl, float elapsedTime)
{
	_logo.setPosition(ctrl.getView().getCenter());
	_rect.setPosition(0,0);
	_rect.setSize(ctrl.getView().getSize());

	_shade_timer += elapsedTime;
	if (1.f < _shade_timer && _shade_timer < 4.17f)
	{
		_shader.setParameter("wave_phase", elapsedTime);
		_shader.setParameter("wave_amplitude", tan(_timer-1) * 50, sin(_shade_timer-1) * 40);
	}
	else if (4.67f < _shade_timer)
	{
		if (!_fading)
		{
			_fading = true;
			_fade.fadeOut();
		}
		else
			_fade.update(ctrl, elapsedTime);
	}

	_timer += elapsedTime;
	if (_fading && !_fade.isFading() || _esc)
	{
		shared_ptr<StateParams> params( new ParamsCtrl(ctrl));
		ctrl.getStateMachine().Change("mainmenu", params);
	}

}

void Splash::Render(Controller& ctrl)
{
	ctrl.getWindow().draw(_rect);
	ctrl.getWindow().draw(_logo, &_shader);

	if (_fading)
		_fade.render(ctrl);
}

bool Splash::handleEvents(const Control& controls)
{
	_esc = controls.isPressed(ESC);
	return false;
}