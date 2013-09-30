#pragma once
#include "types.hpp"

class Register
	{
	
	Word value;

public:
	Register(const Word initialValue = 0);
	virtual Word read() const;
	virtual void write(const Word value);
	};
