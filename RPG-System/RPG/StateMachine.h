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
	//	while (!_states.empty())
	}
	void Render(sf::RenderWindow& window) {	_state_stack.top()->Render(window); }
	bool Update(Controller& ctrl, float elapsedTime) { return _state_stack.top()->Update(ctrl, elapsedTime); }
	void Stack(std::string state, StateParams* params = NULL) 
	{ 
		if (params)
			_state_stack.push(_states[state]->make(params));
		else _state_stack.push(_states[state]->make()); 
	}
	void Pop() { 
		if (!_state_stack.empty())
		{
			_state_stack.pop();
		}
	}
	void Change(std::string state, StateParams* params = NULL) 
	{
		delete _state_stack.top();
		Pop();
		Stack(state, params);
	}
	void Add(std::string desc, StateFactory* factory)
	{
		_states[desc] = factory;
	}


private:
	std::stack<State*> _state_stack;
	std::map<std::string, StateFactory*> _states;
};