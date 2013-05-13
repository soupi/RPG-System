#pragma once

#include <SFML\Graphics.hpp>
#include <stack>
#include <map>
#include <string>
#include "State.h"
#include "StateFactory.h"
#include "StateParams.h"
#include "EmptyState.h"


class Controller;

class StateMachine 
{
public:
	StateMachine()  { _state_stack.push(new EmptyState); }
	~StateMachine() 
	{
		while (!_state_stack.empty())
			Pop();
	//	while (!_states.empty())
	}
	void Render(sf::RenderWindow& window) {	_state_stack.top()->Render(window); }
	bool Update(Controller& ctrl, float elapsedTime) { return _state_stack.top()->Update(ctrl, elapsedTime); }
	void Stack(std::string state, StateParams* params = NULL) 
	{ 
		if (params)
			_state_stack.push(_states[state]->Enter(params));
		else _state_stack.push(_states[state]->Enter()); 
	}
	void Pop() { 
		if (!_state_stack.empty())
		{
			if (_state_stack.top()->Exit())
				delete _state_stack.top();
			_state_stack.pop();
		}
	}
	void Change(std::string state, StateParams* params = NULL) 
	{
		Pop();
		Stack(state, params);
	}
	void Add(std::string desc, State* state)
	{
		_states[desc] = state;
	}


private:
	std::stack<State*> _state_stack;
	std::map<std::string, State*> _states;
};