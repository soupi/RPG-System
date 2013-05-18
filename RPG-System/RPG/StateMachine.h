// The state machine controls and changes the state of the game.

#pragma once

#include <SFML\Graphics.hpp>
#include <stack>
#include <map>
#include <string>
#include "State.h"
#include "StateFactory.h"
#include "StateParams.h"
#include "EmptyState.h"
#include "Control.h"

using std::map;
using std::string;
using std::stack;

class Controller;

class StateMachine 
{
public:
	// Constructor for the state machine is initiallized with an empty state.
	StateMachine()  { _state_stack.push(new EmptyState); }
	// The Destructor deletes the allocated pointers in the state machine
	~StateMachine() 
	{
		while (!_state_stack.empty())
			Pop();
		for (map<string, State*>::iterator it = _states.begin(); it != _states.end(); ++it)
			delete (*it).second;
	}
	// the render function renders the all states on the stack state
	void Render(sf::RenderWindow& window) 
	{
		_state_stack.top()->Render(window); 
	}

	virtual bool handleEvents(const Control& controls) { return _state_stack.top()->handleEvents(controls); }
	// the update function updates the current state
	void Update(Controller& ctrl, float elapsedTime) { _state_stack.top()->Update(ctrl, elapsedTime); }
	// stacks a state on top of the current state
	void Stack(std::string state, StateParams* params = NULL) 
	{ 
		// enter a new state
		if (params) 
			_state_stack.push(_states[state]->Enter(params));
		else _state_stack.push(_states[state]->Enter()); 
	}
	// pop the current state -> back to the previous state.
	void Pop() { 
		if (!_state_stack.empty())
		{
			if (_state_stack.top()->Exit())
				delete _state_stack.top();
			_state_stack.pop();
		}
	}
	// changes the current state
	void Change(std::string state, StateParams* params = NULL) 
	{
		Pop();
		Stack(state, params);
	}
	// adds a state to state machine so we will be able to use it in the future.
	void Add(std::string desc, State* state)
	{
		_states[desc] = state;
	}


private:
	stack<State*> _state_stack;
	map<string, State*> _states;
};