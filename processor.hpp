#include "register.hpp"
#include "types.hpp"


#include <vector>



class Processor
	{

	std::vector <Register> registers; // The first register should be a zero-register
	std::vector <Word> mainMemory; // This should be larger, but will require a clever datastructure
	Word programCounter;

public:
	Processor(int startingAddress, const std::vector <Word>& initialMemory);

	Register& getRegister(const int regNumber) const;
	Word& getWord(const Word address) const;
	Word getProgramCounter() const;
	void changeProgramCounter(const int change);

	void exec();

	};
