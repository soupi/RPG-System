// The state machine controls and changes the state of the game.

#pragma once

#include <SFML\Graphics.hpp>
#include <stack>
#include <map>
#include <string>
#include "State.h"
#include "StateParams.h"
#include "EmptyState.h"
#include "Control.h"
#include <memory>

using std::shared_ptr;
using std::map;
using std::string;
using std::stack;

class Controller;

class StateMachine 
{
public:
	// Constructor for the state machine is initiallized with an empty state.
	StateMachine()  { _state_stack.push(shared_ptr<State>(new EmptyState)); }
	// The Destructor deletes the allocated pointers in the state machine
	~StateMachine() 
	{
		while (!_state_stack.empty())
			Pop();
	}
	// the render function renders the all states on the stack state
	void Render(Controller& ctrl) 
	{
		_state_stack.top()->Render(ctrl); 
	}

	virtual bool handleEvents(const Control& controls) { return _state_stack.top()->handleEvents(controls); }
	// the update function updates the current state
	void Update(Controller& ctrl, float elapsedTime) { _state_stack.top()->Update(ctrl, elapsedTime); }
	// stacks a state on top of the current state
	void Stack(std::string state, shared_ptr<StateParams>& params) 
	{ 
		// enter a new state
		
		_state_stack.push(_states[state]);
		_state_stack.top()->Enter(params);
	}
	// pop the current state -> back to the previous state.
	void Pop() { 
		if (!_state_stack.empty())
		{
			_state_stack.top()->Exit();
			_state_stack.pop();
		}
	}
	// changes the current state
	void Change(std::string state, shared_ptr<StateParams>& params) 
	{
		Pop();
		Stack(state, params);
	}
	// adds a state to state machine so we will be able to use it in the future.
	void Add(std::string desc, shared_ptr<State>& state)
	{
		_states[desc] = state;
	}


private:
	stack<shared_ptr<State>> _state_stack;
	map<string, shared_ptr<State>> _states;
};