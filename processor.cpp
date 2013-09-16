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
	// This is roughly the I stage
	Word instruction = this->getWord(programCounter);
	programCounter += 4;
	char opcode = instruction >> 32-6; // This should get the upper six bits of the instruction
	char funct = instruction & 0x3f; // Get the lower 6 bits in case this is a R format
	
	Register rs = this->getRegister(0x03f80000 & instruction); 
	Register rt = this->getRegister(0x001f0000 & instruction);
	char im = 0x0000ffff & instruction;
	Register rd = this->getRegister(0x0000fc00 & instruction);
	char sh = 0x000003c0 & instruction;

	// E stage
	switch (opcode)
		{
		case 0 : break;
		case 2 : this->j(instruction|0x03ffffff); break;
		case 3 : this->jal(instruction|0x03ffffff); break;
		case 4 : this->beq(rs,rt,im); break;
		case 5 : this->bne(rs,rt,im); break;
		case 6 : case 7 : break; // Not specified
		case 8 : this->addi(rs,rt,im); break;
		case 9 : this->addiu(rs,rt,im); break;
		case 10: this->slti(rs,rt,im); break;
		case 11: break; // Not specified
		case 12: this->andi(rs,rt,im); break;
		case 13: this->ori(rs,rt,im); break;
		case 14: break; // Not specified
		case 15: this->lui(rs,rt,im); break;
		
		case 32: this->lb(rs,rt,im); break; // Load byte
		case 33: this->lh(rs,rt,im); break; // Load halfword
		case 34: break; // Not specified
		case 35: this->lw(rs,rt,im); break;
		case 36: this->lbu(rs,rt,im); break; // Load unsigned byte
		case 37: this->lhu(rs,rt,im); break;
		case 38: case 39: break; // Not specified
		case 40: this->sb(rs,rt,im); break; // Store byte
		case 41: this->sh(rs,rt,im); break;
		case 42: break; // Not specified
		case 43: this->sw(rs,rt,im); break;
		default: break;
		}
	
	if (!opcode)
		{
		switch (funct)
			{
			case 0 : this->sll(rs,rt,rd,sh); break;
			case 1 : break; // Not specified
			case 2 : this->srl(rs,rt,rd,sh); break;
			case 3 : this->sra(rs,rt,rd,sh); break;
			case 8 : this->jr(rs,rt,rd,sh); break;
			case 16: this->mfhi(rs,rt,rd,sh); break;
			case 18: this->mflo(rs,rt,rd,sh); break;
			case 24: this->mult(rs,rt,rd,sh); break;
			case 25: this->multu(rs,rt,rd,sh); break;
			case 26: this->div(rs,rt,rd,sh); break;
			case 27: this->divu(rs,rt,rd,sh); break;

			case 32: this->add(rs,rt,rd,sh); break;
			case 33: this->addu(rs,rt,rd,sh); break;
			case 34: this->sub(rs,rt,rd,sh); break;
			case 35: this->subu(rs,rt,rd,sh); break;
			case 36: this->andd(rs,rt,rd,sh); break;
			case 37: this->orr(rs,rt,rd,sh); break;
			case 38: this->xorr(rs,rt,rd,sh); break;
			case 39: this->nor(rs,rt,rd,sh); break;
			case 42: this->slt(rs,rt,rd,sh); break;
			}
		}

