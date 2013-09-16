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

	// Operations
	void j(const Word address);
	void jal(const Word address);
	void beq(const Register rs, const Register rt, const Word im);
	void bne(const Register rs, const Register rt, const Word im);
	void addi(Register rs, const Register rt, const Word im) const;
	void addiu(Register rs, const Register rt, const Word im) const;
	void slti(Register rs, const Register rt, const Word im) const;
	void andi(Register rs, const Register rt, const Word im) const;
	void ori(Register rs, const Register rt, const Word im) const;
	void lui(Register rs, const Register rt, const Word im) const;
	void lb(Register rs, const Register rt, const Word im) const;
	void lh(Register rs, const Register rt, const Word im) const;
	void lw(Register rs, const Register rt, const Word im) const;
	void lbu(Register rs, const Register rt, const Word im) const;
	void lhu(Register rs, const Register rt, const Word im) const;
	void sb(Register rs, const Register rt, const Word im) const;
	void sh(Register rs, const Register rt, const Word im) const;
	void sw(Register rs, const Register rt, const Word im) const;

	// Functions
	void sll(const Register rs, const Register rt, Register rd, const Word sh) const;
	void srl(const Register rs, const Register rt, Register rd, const Word sh) const;
	void sra(const Register rs, const Register rt, Register rd, const Word sh) const;
	void jr(const Register rs, const Register rt, const Register rd, const Word sh);
	void mfhi(const Register rs, const Register rt, Register rd, const Word sh) const;
	void mflo(const Register rs, const Register rt, Register rd, const Word sh) const;
	void mult(const Register rs, const Register rt, const Register rd, const Word sh);
	void multu(const Register rs, const Register rt, const Register rd, const Word sh);
	void div(const Register rs, const Register rt, const Register rd, const Word sh);
	void divu(const Register rs, const Register rt, const Register rd, const Word sh);
	void add(const Register rs, const Register rt, Register rd, const Word sh) const;
	void addu(const Register rs, const Register rt, Register rd, const Word sh) const;
	void sub(const Register rs, const Register rt, Register rd, const Word sh) const;
	void subu(const Register rs, const Register rt, Register rd, const Word sh) const;
	void andd(const Register rs, const Register rt, Register rd, const Word sh) const;
	void orr(const Register rs, const Register rt, Register rd, const Word sh) const;
	void xorr(const Register rs, const Register rt, Register rd, const Word sh) const;
	void nor(const Register rs, const Register rt, Register rd, const Word sh) const;
	void slt(const Register rs, const Register rt, Register rd, const Word sh) const;
	};
