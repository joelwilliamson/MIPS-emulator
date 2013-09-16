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

void Processor::j(const Word address)
	{
	programCounter = 4*address;
	}

void Processor::jal(const Word address)
	{
	// The instruction immediately following the jump should be
	// executed before the jump, but I am diverging from the spec
	// by ignoring it
	registers.at(31).write(programCounter + 4);
	programCounter = 4*address;
	}

void Processor::beq(const Register& rs, const Register& rt, const Word im)
	{
	if (rs.read() != rt.read()) return;
	else programCounter += 4*im;
	}

void Processor::bne(const Register& rs, const Register& rt, const Word im)
	{
	if (rs.read() == rt.read()) programCounter += 4*im;
	}

void Processor::addi(const Register& rs, Register& rt, const Word im) const
	{
	rt.write(rs.read()+im);
	}

void Processor::addiu(const Register& rs, Register& rt, const Word im) const
	{
	// TODO: implement
	throw 0;
	}

void Processor::slti(const Register& rs, Register &rt, const Word im) const
	{
	rt.write(rs.read()<im);
	}

void Processor::andi(const Register& rs, Register& rt, const Word im) const
	{
	rt.write(rs.read() & im);
	}

void Processor::ori(const Register& rs, Register& rt, const Word im) const
	{
	rt.write(rs.read() & im);
	}

void Processor::lui(const Register& rs, Register& rt, const Word im) const
	{
	rt.write(im << 16);
	}

void Processor::lb(const Register& rs, Register& rt, const Word im) const
	{
	// Get the appropriate word and select the appropriate byte
	rt.write(this->getWord((rs.read()+im)/4)
			<< 8*((rs.read()+im)%4));
	}

void Processor::lh(const Register& rs, Register& rt, const Word im) const
	{
	rt.write(this->getWord((rs.read()+im)/4)
			<< 16*((rs.read()+im)%8));
	}

void Processor::lw(const Register& rs, Register& rt, const Word im) const
	{
	rt.write(this->getWord((rs.read()+im)/4));
	}

void Processor::lbu(const Register& rs, Register& rt, const Word im) const
	{
	// TODO: implement
	throw 0;
	}

void Processor::lhu(const Register& rs, Register& rt, const Word im) const
	{
	// TODO: implement
	throw 0;
	}

void Processor::sb(const Register& rs, const Register& rt, const Word im) const
	{
	// TODO: think about this, implement it correctly
	throw 0;
	Word addr = (rs.read()+im)/4;
	Word oldValue = this->getWord(addr);
	Word mask = 0xffffffff - (0xff << 3-(rs.read()+im)%4);
	Word newValue = (rt.read()&0xff) << 3-(rs.read()+im)%4;
	this->getWord(addr) = (oldValue&mask) + newValue;
	}

void Processor::sh(const Register& rs, const Register& rt, const Word im) const
	{
	throw 0;
	}

void Processor::sw(const Register& rs, const Register& rt, const Word im) const
	{
	this->getWord((rs.read()+im)/4) = rt.read();
	}

void Processor::sll(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	rd.write(rt.read() << sh);
	}

void Processor::srl(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	rd.write(rt.read() >> sh);
	}

void Prcoessor::sra(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	throw 0;
	}

void Processor::jr(const Register& rs, const Register& rt, Register& rd, const Word sh)
	{
	this->j(rs.read());
	}

void Processor::mfhi(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	rd.write(hi.read());
	}

void Processor::mflo(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	rd.write(lo.read());
	}

void Processor::mult(const Register& rs, const Register& rt, const Register& rd, const Word sh)
	{
	uint64_t product = rs.read()*rt.read();
	lo.write(product()&0xffffffff);
	hi.write(product() >> 32);
	}

void Processor::multu(const Register& rs, const Register& rt, const Register& rd, const Word sh)
	{
	throw 0;
	}

void Processor::div(const Register& rs, const Register& rt, const Register& rd, const Word sh)
	{
	lo.write(rs.read()/rt.read());
	hi.write(rs.read()%rt.read());
	}

void Processor::divu(const Register& rs, const Register& rt, const Register& rd, const Word sh)
	{
	throw 0;
	}

void Processor::add(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	rd.write(rs.read()+rt.read());
	}

void Processor::addu(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	throw 0;
	}

void Processor::sub(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	rd.write(rs.read()-rt.read());
	}

void Processor::subu(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	throw 0;
	}

void Processor::andd(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	rd.write(rs.read() & rt.read());
	}

void Processor::orr(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	rd.write(rs.read() | rt.read());
	}

void Processor::xorr(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	rd.write(rs.read() ^ rt.read());
	}

void Processor::nor(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	// A nor B = not (A or B) = (not A) and (not B)
	rd.write((rs.read()^0) & (rt.read()^0));
	}

void Processor::slt(const Register& rs, const Register& rt, Register& rd, const Word sh) const
	{
	rd.write(rs.read()<rt.read());
	}
