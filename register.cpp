#include "register.hpp"

Word read() const
	{
	return value;
	}

void write(const Word value)
	{
	this.value = value;
	}
