#include <iostream>
#include "processor.hpp"

template <typename BaseProcessor>
class simple_io : public BaseProcessor
{
public:
  using BaseProcessor::BaseProcessor;
  void dump_reg(const Register& rs) const;
};

template<typename BaseProcessor>
void simple_io<BaseProcessor>::dump_reg(const Register& rs) const
{
  std::cout << rs.read() << std::endl;
}
template <typename BaseProcessor>
class trapped_overflow : public BaseProcessor
{
  bool trap_;
  Word trap_location_;
public:
  using BaseProcessor::BaseProcessor;
  bool trap() const
  {
    return trap_;
  }

  Word trap_location() const
  {
    return trap_location_;
  }

  void clear_trap()
  {
    trap_ = false;
    trap_location_ = 0;
  }

  void add(const Register& rs, const Register& rt, Register& rd, Word sh) override
  {
    int32_t ss = rs.read(), st = rt.read();
    int32_t sum = ss + st;
    bool overflow = (ss & 1<<31) == (st & 1<<31) && (ss & 1<<31) != (sum & 1<<31);
    if (overflow) {
      trap_ = true;
      trap_location_ = BaseProcessor::getProgramCounter();
    } else {
      rd = sum;
    }
  }

  void sub(const Register& rs, const Register& rt, Register& rd, Word sh) override
  {
    int32_t ss = rs.read(), st = rt.read();
    int32_t diff = ss - st;
    bool overflow = (ss & 1<<31) == (st & 1<<31) && (ss & 1<<31) != (diff & 1<<31);
    if (overflow) {
      trap_ = true;
      trap_location_ = BaseProcessor::getProgramCounter();
    } else {
      rd = diff;
    }
  }

  void addi(const Register& rs, Register& rt, Word im) override
  {
    Word ss = rs.read(), sum = ss + im;
    bool overflow = (ss & 1<<31) == (im & 1<<31) && (ss & 1<<31) != (sum & 1<<31);
    if (overflow) {
      trap_ = true;
      trap_location_ = BaseProcessor::getProgramCounter();
    } else {
      rt = sum;
    }
  }
};
