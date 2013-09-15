#include "types.hpp"

class Register
	{
	
	Word value;

public:
	virtual Word read() const;
	virtual void write(const Word value);
	};
