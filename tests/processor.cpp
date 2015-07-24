#define BOOST_TEST_MODULE processor_tests
#include <boost/test/included/unit_test.hpp>

#include "../processor.hpp"

BOOST_AUTO_TEST_CASE( processor_test ) {
  Processor proc(0,{});
  Register& r1 = proc.getRegister(1);
  Register& r2 = proc.getRegister(2);
  Register& r3 = proc.getRegister(3);
  r1 = 4;
  r2 = 7;
  // 4 + 7 == 11
  proc.add(r1,r2,r3,0);
  BOOST_CHECK( r3.read() == 11 );
  // 7 << 5 == 224
  proc.sll(r1,r2,r3,5);
  BOOST_CHECK( r3.read() == 224 );

  // r2 >> sh
  proc.srl(r1,r2,r3,1);
  BOOST_CHECK( r3.read() == 3 );

}
