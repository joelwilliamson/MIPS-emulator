#include <iostream>
#include <vector>

#include "register.hpp"
#include "processor.hpp"
#include "types.hpp"

/*Word program[] = {0x20020000,// addi $2,$0,0
		 0x20030001, // addi $3,$0,1
		 0x00212014, // add $4,$1,$1
		 0x20050001, // addi $5,$0,1
		 0x00852015, // sub $4,$4,$5
		 0x00431014, // add $2,$2,$3
		 0x20630002, // addi $3,$3,2
		 0x1464fffd, // bne $3,$4,-3
//		 0x08000000, // j 0
		 0x00000000};
		 */

Word program[] = {0x200200ff, // addi $2,$0,0x00ff
		0x20420fff, // addi $2,$2,0x0fff
		0x00000000};

int main()
	{
	std::vector <Word> progVector(program,program+(sizeof(program)/sizeof(program[0])));
	std::cerr.setf(std::ios_base::hex,std::ios_base::hex | std::ios_base::dec);
	for (auto elem : progVector)
		std::cerr << elem << std::endl;
	Processor nP(0,progVector);
	nP.getRegister(1).write(4);
	std::cerr << "Set first register to " << nP.getRegister(1).read() << std::endl;
	while (nP.getWord(nP.getProgramCounter()))
		nP.exec();
	
	std::cout << "fff+ff = " << nP.getRegister(2).read() << std::endl;
	}
