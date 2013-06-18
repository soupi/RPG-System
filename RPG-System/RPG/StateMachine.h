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
	// Constructor
	StateMachine(); 
	// Destructor
	~StateMachine();

	void Render(Controller& ctrl);
	bool handleEvents(const Control& controls);
	void Update(Controller& ctrl, float elapsedTime);
	void Stack(std::string state, shared_ptr<StateParams>& params);
	void Pop();
	void Change(std::string state, shared_ptr<StateParams>& params);
	void Add(std::string desc, shared_ptr<State>& state);

private:
	stack<shared_ptr<State>> _state_stack;
	map<string, shared_ptr<State>> _states;
};