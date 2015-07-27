#pragma once
#include "register.hpp"
#include "types.hpp"


#include <vector>

/* The Processor class represents the state of a non-pipelined MIPS processor.
 * At any given instant, it has a program counter indicating which instruction
 * to execute next, a bank of 32 registers (each 32-bits wide) of easily
 * accessible storage, and an arbitrarily sized main memory.
 *
 * Most interaction with the processor should go through the "Operation" and
 * "Function" methods, which represent opcodes. To simulate a full run on a
 * program in memory, the `exec()` function will start execution at an address
 * specfied at construction time, and use real program flow.
 *
 * To implement interaction with off-processor resources (e.g. IO, control
 * coprocessor, FPU, etc.), the processor will maintain a count of how many
 * instructions it has executed. Periodically, it will yield to the caller,
 * who can deal with any other resources. The caller than then reenter the
 * processor execution, restarting the counter.
 *
 * For off-chip resources, probably a CRTP-style inheritance, with each
 * resource maintaining a queue of signals, and the call handler can empty
 * each queue when control is transferred to it.
 */
class Processor
{

  Word programCounter;
  std::vector <Register> registers; // The first register should be a zero-register
  std::vector <Word> mainMemory; // This should be larger, but will require a clever datastructure

  Register hi,lo; // Registers for storing the results of certain operations
public:
  Processor(int startingAddress, const std::vector <Word>& initialMemory);

  Register& getRegister(const Word regNumber);
  Word& getWord(const Word address);
  Word getProgramCounter() const;
  void changeProgramCounter(const int change);

  // Step the processor one instruction
  void exec();

	// Operations
	void j(const Word address);
	void jal(const Word address);
	void beq(const Register& rs, const Register& rt, const Word im);
	void bne(const Register& rs, const Register& rt, const Word im);
	void addi(const Register& rs, Register& rt, const Word im) const;
	void addiu(const Register& rs, Register& rt, const Word im) const;
	void slti(const Register& rs,  Register& rt, const Word im) const;
	void andi(const Register& rs,  Register& rt, const Word im) const;
	void ori(const Register& rs,  Register& rt, const Word im) const;
	void lui(const Register& rs,  Register& rt, const Word im) const;
	void lb(const Register& rs,  Register& rt, const Word im);
	void lh(const Register& rs,  Register& rt, const Word im);
	void lw(const Register& rs,  Register& rt, const Word im);
	void lbu(const Register& rs,  Register& rt, const Word im);
	void lhu(const Register& rs, Register& rt, const Word im);
	void sb(const Register& rs, const Register& rt, const Word im);
	void sh(const Register& rs, const Register& rt, const Word im);
	void sw(const Register& rs, const Register& rt, const Word im);

	// Functions
	void sll(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	void srl(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	void sra(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	void jr(const Register& rs, const Register& rt, const Register& rd, const Word sh);
	void mfhi(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	void mflo(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	void mult(const Register& rs, const Register& rt, const Register& rd, const Word sh);
	void multu(const Register& rs, const Register& rt, const Register& rd, const Word sh);
	void div(const Register& rs, const Register& rt, const Register& rd, const Word sh);
	void divu(const Register& rs, const Register& rt, const Register& rd, const Word sh);
	void add(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	void addu(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	void sub(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	void subu(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	void andd(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	void orr(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	void xorr(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	void nor(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	void slt(const Register& rs, const Register& rt, Register& rd, const Word sh) const;
	};
