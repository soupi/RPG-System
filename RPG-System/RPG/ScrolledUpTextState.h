#include "TextState.h"
#include "Macros.h"

class ScrolledUpTextState : public TextState
{
public:
	ScrolledUpTextState(const string& str) : TextState(str) { }
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Enter(shared_ptr<StateParams>& params);
};