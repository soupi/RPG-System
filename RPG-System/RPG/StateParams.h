#pragma once

#include <string>
using std::string;

class Controller;

class StateParams {
public:
	virtual ~StateParams() {}
	virtual Controller& getCtrl() = 0;
};