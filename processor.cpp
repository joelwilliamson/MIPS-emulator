#include "processor.hpp"

#include <algorithm>

Processor::Processor(int startingAddress, const std::vector <Word>& initialMemory)
	: programCounter(startingAddress),
	registers(32),
	mainMemory(2000)
	{
	registers.at(0).write(0); // Zero out the first register
	std::copy(initialMemory.begin(),initialMemory.end(),mainMemory.begin());
	}

Register& Processor::getRegister(const int regNumber) const
	{
	return registers.at(regNumber);
	}

Word& Processor::getWord(const Word address) const
	{
	return mainMemory.at(address);
	}

Word Processor::getProgramCounter() const
	{
	return programCounter;
	}

void Processor::changeProgramCounter(const int change)
	{
	programCounter+= change;
	}

void Processor::exec()
	{
	Word instruction = this->getWord(programCounter);
	programCounter += 4;
	char opcode = instruction >> 32-6; // This should get the upper six bits of the instruction
	char funct = instruction & 0x3f; // Get the lower 6 bits in case this is a R format
	
	char rs = 0x03f80000 & instruction; 
	char rt = 0x001f0000 & instruction;
	char im = 0x0000ffff & instruction;
	char rd = 0x0000fc00 & instruction;
	char sh = 0x000003c0 & instruction;

	switch (opcode)
		{
		case 0 : break;
		case 2 : j(instruction|0x03ffffff); break;
		case 3 : jal(instruction|0x03ffffff); break;
		case 4 : beq(rs,rt,im); break;
		case 5 : bne(rs,rt,im); break;
		case 6 : case 7 : break; // Not specified
		case 8 : addi(rs,rt,im); break;
		case 9 : addiu(rs,rt,im); break;
		case 10: slti(rs,rt,im); break;
		case 11: break; // Not specified
		case 12: andi(rs,rt,im); break;
		case 13: ori(rs,rt,im); break;
		case 14: break; // Not specified
		case 15: lui(rs,rt,im); break;
