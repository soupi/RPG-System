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
	ParamsMap(Controller& ctrl, const string& map_name, unsigned starting_tile) : _map_name(map_name), _starting_tile(starting_tile),ParamsCtrl(ctrl) {}
	const string& getMap() const { return _map_name; }
	const unsigned& StartingTile() const { return _starting_tile; }

private:
	string _map_name;
	unsigned _starting_tile;
};