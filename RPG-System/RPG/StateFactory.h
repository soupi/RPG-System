#pragma once

#include "State.h"
#include "StateParams.h"

class StateFactory {
public:
	virtual ~StateFactory() { }
	virtual State* make(StateParams* params = NULL) = 0;

};

template <class T>

class StateFactoryT : public StateFactory 
{
public:
	virtual T* make(StateParams* params = NULL)
	{
		if (params)
			return new T(params);
		return new T;
	}
};