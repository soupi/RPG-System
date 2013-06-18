#include "TextState.h"

class GameOver : public TextState
{
public:
	GameOver() : TextState("GAME OVER.") { }
	virtual bool handleEvents(const Control& controls) { return (controls.isPressed(ENTER) || controls.isPressed(ESC)); }
};