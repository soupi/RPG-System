#pragma once

#include "Script.h"


class IFScript : public Script
{
public:
	virtual ~IFScript() { }


protected:
	Script* _if_script;
	Script* _else_script;
	bool _if;
};

class IFLevel : public IFScript
{

};
class IFQItem : public IFScript
{

};