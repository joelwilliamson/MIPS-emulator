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
  // srl handles negative values correctly (non-sign preserving)
  r2 = 0xffffffff;
  proc.srl(r1,r2,r3,4);
  BOOST_CHECK( r3.read() == 0x0fffffff );

  // sra
  r2 = 0x0fffffff;
  proc.sra(r1,r2,r3,4);
  BOOST_CHECK( r3.read() == 0x00ffffff );
  r2 = 0xffffff00;
  proc.sra(r1,r2,r3,4);
  BOOST_CHECK( r3.read() == 0xfffffff0 );

  // jump to register
  r1 = 0xdeadbeef;
  proc.jr(r1,r2,r3,0);
  BOOST_CHECK( proc.getProgramCounter() == 0xdeadbeef );

  // multiply signed
  r1 = 5784;
  r2 = 9865;
  proc.mult( r1, r2, r3, 0);
  proc.mflo( r1, r2, r3, 0);
  BOOST_CHECK( r3.read() == 5784 * 9865 );

  r1 = -435;
  r2 = 928;
  proc.mult( r1, r2, r3, 0);
  proc.mflo( r1, r2, r3, 0);
  BOOST_CHECK( r3.read() == Word(-435 * 928) );
  proc.mfhi( r1, r2, r3, 0);
  BOOST_CHECK( r3.read() == 0xffffffff);
}
