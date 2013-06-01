#pragma once

#include "State.h"

template <class T>
class StateFactory : public State
{
public:


	class IState : public State 
	{
	public:
		virtual bool Update(Controller& ctrl, float elapsedTime) { return _state.Update(ctrl, elapsedTime); }
		virtual void Render(Controller& ctrl) { _state.Render(ctrl); }
		virtual State* Enter(shared_ptr<StateParams>& paramsL) 
		{ 
			if (params) 
				_state.Enter(params);
			else _state.Enter(); 
			return this;
		}
		virtual bool Exit() { _state.Exit(); return true; }

	private:
		T _state;
	};


	virtual State* Enter(shared_ptr<StateParams>& params)
	{
		IState* state = new IState;
		return state->Enter(params);
	}

	virtual bool Update(Controller&, float elapsedTime) { return false; }
	virtual void Render(Controller& ctrl) { }
};