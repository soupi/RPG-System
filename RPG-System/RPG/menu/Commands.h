// In this file is the definition of a few command classes.
// a command class holds an certain execution that can be executed by pressing a button for instance.

#pragma once

#include "Command.h"
#include "../StateMachine.h"
#include "../ParamsMap.h"

class Pause;

class StartGame : public Command
{
public:
	StartGame(StateMachine& machine, shared_ptr<ParamsMap> params) : _machine(machine), _params(params) {}
	void execute() { _machine.Change("localmap", _params); }
private:
	StateMachine& _machine;
	shared_ptr<StateParams> _params;
};

class RunHelp : public Command
{
public:
	RunHelp(StateMachine& machine, shared_ptr<StateParams> params) : _machine(machine), _params(params) {}
	void execute() { _machine.Stack("help", _params); }
private:
	StateMachine& _machine;
	shared_ptr<StateParams> _params;
};

class PopState : public Command
{
public:
	PopState(StateMachine& machine) : _machine(machine) {}
	void execute() { _machine.Pop(); }
private:
	StateMachine& _machine;
};

class PauseEscape : public Command
{
public:
	PauseEscape(Pause& pause) : _pause(pause) {}
	void execute();
private:
	Pause& _pause;
};