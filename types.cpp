#include "types.hpp"

int32_t toSigned (Word value, int precision)
	{
	// If the sign bit is 0, return unchanged
	if (!(value & (1 << (precision-1)))) return value;
	uint32_t mask = 0;
	for (int i = 0; i < precision; ++i)
		{
		mask <<=1;
		mask += 1;
		}
	
	return (-(value + 1) ^ mask);
	}
