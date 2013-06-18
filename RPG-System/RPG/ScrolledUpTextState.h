#include "TextState.h"
#include "Macros.h"

// a state where the text entered in the constructor rises up until the middle of the screen

class ScrolledUpTextState : public TextState
{
public:
	ScrolledUpTextState(const string& str) : TextState(str) { }
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Enter(shared_ptr<StateParams>& params);
};