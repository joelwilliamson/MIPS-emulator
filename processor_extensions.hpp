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
  std::cout << rs.read();
}
