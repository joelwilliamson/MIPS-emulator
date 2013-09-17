#include <iostream>
#include <vector>

#include "register.hpp"
#include "processor.hpp"
#include "types.hpp"

int program[] = {0x20020000,
		 0x20030001,
		 0x00212014,
		 0x20050001,
		 0x00852015,
		 0x00431014,
		 0x20630002,
		 0x0464fffd};

int main()
	{
	std::vector <Word> progVector(program,program+8);
	Processor nP(0,progVector);
	nP.getRegister(1).write(4);
	while (nP.getWord(nP.getProgramCounter()))
		nP.exec();
	
	std::cout << "4^2 = " << nP.getRegister(2).read() << std::endl;
	}
