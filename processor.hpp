#include "register.hpp"
#include "types.hpp"


#include <vector>



class Processor
	{

	std::vector <Register> registers; // The first register should be a zero-register
	std::vector <Word> mainMemory; // This should be larger, but will require a clever datastructure
	Word programCounter;

	Register hi,lo; // Registers for storing the results of certain operations

public:
	Processor(int startingAddress, const std::vector <Word>& initialMemory);

	Register& getRegister(const int regNumber) const;
	Word& getWord(const Word address) const;
	Word getProgramCounter() const;
	void changeProgramCounter(const int change);

	void exec();

	// TODO: All registers should be passed by reference
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
	void lb(const Register& rs,  Register& rt, const Word im) const;
	void lh(const Register& rs,  Register& rt, const Word im) const;
	void lw(const Register& rs,  Register& rt, const Word im) const;
	void lbu(const Register& rs,  Register& rt, const Word im) const;
	void lhu(const Register& rs, Register& rt, const Word im) const;
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
