// In this file is the definition of a few command classes.
// a command class holds an certain execution that can be executed by pressing a button for instance.

#pragma once

#include "Command.h"
#include "../StateMachine.h"
#include "../ParamsMap.h"

class Pause;

// changes the state to "localmap" with the parameters it receives
class StartGame : public Command
{
public:
	StartGame(StateMachine& machine, shared_ptr<StateParams> params) : _machine(machine), _params(params) {}
	void execute() { _machine.Change("intro", _params); }
private:
	StateMachine& _machine;
	shared_ptr<StateParams> _params;
};

// runs the help state

class RunHelp : public Command
{
public:
	RunHelp(StateMachine& machine, shared_ptr<StateParams> params) : _machine(machine), _params(params) {}
	void execute() { _machine.Stack("help", _params); }
private:
	StateMachine& _machine;
	shared_ptr<StateParams> _params;
};

class RunCredits : public Command
{
public:
	RunCredits(StateMachine& machine, shared_ptr<StateParams> params) : _machine(machine), _params(params) {}
	void execute() { _machine.Stack("credits", _params); }
private:
	StateMachine& _machine;
	shared_ptr<StateParams> _params;
};

// pops the current state in the game state stack

class PopState : public Command
{
public:
	PopState(StateMachine& machine) : _machine(machine) {}
	void execute() { _machine.Pop(); }
private:
	StateMachine& _machine;
};

// sets pause's _escape to true when command is executed

class PauseEscape : public Command
{
public:
	PauseEscape(Pause& pause) : _pause(pause) {}
	void execute();
private:
	Pause& _pause;
};