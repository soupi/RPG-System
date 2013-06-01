#include "Script.h"

class NoScript : public Script
{
public:
	virtual bool handleEvents(const Control& controls) { return false; }
	virtual bool Update(Controller&, float elapsedTime) { return false; }
	virtual void Render(Controller& ctrl) {}
private:
	virtual void enter(Hero& hero) {}
	virtual void exit() {}
};