#pragma once

class Controller;

class StateParams {
public:
	virtual ~StateParams() {}
	virtual Controller& getCtrl() = 0;
};