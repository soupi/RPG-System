#include "StateMachine.h"

// Constructor for the state machine is initiallized with an empty state.
StateMachine::StateMachine()  
{ 
	_state_stack.push(shared_ptr<State>(new EmptyState)); 
}
// The Destructor deletes the allocated pointers in the state machine
StateMachine::~StateMachine() 
{
	while (!_state_stack.empty())
		Pop();
}
// the render function renders the all states on the stack state
void StateMachine::Render(Controller& ctrl) 
{
	_state_stack.top()->Render(ctrl); 
}
// handle events
bool StateMachine::handleEvents(const Control& controls) 
{ 
	return _state_stack.top()->handleEvents(controls); 
}
// the update function updates the current state
void StateMachine::Update(Controller& ctrl, float elapsedTime) 
{ 
	_state_stack.top()->Update(ctrl, elapsedTime); 
}
// stacks a state on top of the current state
void StateMachine::Stack(std::string state, shared_ptr<StateParams>& params) 
{ 
	// enter a new state
		
	_state_stack.push(_states[state]);
	_state_stack.top()->Enter(params);
}
// pop the current state -> back to the previous state.
void StateMachine::Pop() { 
	if (!_state_stack.empty())
	{
		_state_stack.top()->Exit();
		_state_stack.pop();
	}
}
// changes the current state
void StateMachine::Change(std::string state, shared_ptr<StateParams>& params) 
{
	Pop();
	Stack(state, params);
}
// adds a state to state machine so we will be able to use it in the future.
void StateMachine::Add(std::string desc, shared_ptr<State>& state)
{
	_states[desc] = state;
}