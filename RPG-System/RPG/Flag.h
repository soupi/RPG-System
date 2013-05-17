#pragma once

class Flag 
{
public:
	Flag(bool flag = false) : _flag(flag) { }
	bool state()
	{
		if (_flag)
		{
			_flag = false;
			return true;
		}
		return false;
	}
	operator bool() { return state(); }
	void set() { _flag = true; }
private:
	bool _flag;
};