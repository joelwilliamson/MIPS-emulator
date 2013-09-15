#include "register.hpp"

Word Register::read() const
	{
	return value;
	}

void Register::write(const Word value)
	{
	this->value = value;
	}
