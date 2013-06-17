/*
 * Header file for class Command.
 * The command is a base class for other command classes
*/
#pragma once


class Command
{
public:
	virtual ~Command() { }
	virtual void execute() = 0;
};