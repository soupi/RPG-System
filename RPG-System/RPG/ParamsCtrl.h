#pragma once

#include "StateParams.h"

class ParamsCtrl : public StateParams
{
public:
	ParamsCtrl(Controller& ctrl) : _ctrl(ctrl) { }
	virtual ~ParamsCtrl() { }
	virtual Controller& getCtrl() { return _ctrl; }
private:
	Controller& _ctrl;
};

#include <string>

using std::string;

class ParamsMap : public ParamsCtrl
{
public:
	ParamsMap(Controller& ctrl, const string& map_name) : _map_name(map_name), ParamsCtrl(ctrl) {}
	const string& getMap() const { return _map_name; }

private:
	string _map_name;
};