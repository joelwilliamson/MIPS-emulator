#include "register.hpp"

Register::Register(const Word initialValue)
	{
	value = initialValue;
	}

Word Register::read() const
	{
	return value;
	}

void Register::write(const Word value)
	{
	this->value = value;
	}
