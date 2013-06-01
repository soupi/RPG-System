#pragma once

#include "State.h"

template <class T>
class StateFactory : public State
{
public:


	class IState : public State 
	{
	public:
		virtual bool handleEvents(const Control& controls) { return _state.handleEvents(controls); }
		virtual void Update(Controller& ctrl, float elapsedTime) { _state.Update(ctrl, elapsedTime); }
		virtual void Render(Controller& ctrl) { _state.Render(ctrl); }
		virtual void Enter(shared_ptr<StateParams>& params) 
		{ 
			_state.Enter(params);
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
	
	virtual bool handleEvents(const Control& controls) { return false; }
	virtual void Update(Controller&, float elapsedTime) {  }
	virtual void Render(Controller& ctrl) { }
};