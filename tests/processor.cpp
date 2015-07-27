#define BOOST_TEST_MODULE processor_tests
#include <boost/test/included/unit_test.hpp>

#include "../processor.hpp"
#include "../processor_extensions.hpp"

BOOST_AUTO_TEST_CASE( processor_test ) {
  simple_io<Processor> proc(0,{0,1,2,3,4,5,6,7,8,10});
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

  // Multiply unsigned
  r1 = 4294967286;
  r2 = 2147541541;
  proc.multu( r1, r2, r3, 0);
  proc.mflo( r1, r2, r3, 0);
  BOOST_CHECK( r3.read() == 4294388366 );
  proc.mfhi( r1, r2, r3, 0);
  BOOST_CHECK( r3.read() == 2147541535 );

  // Divide signed
  r1 = 137;
  r2 = 30;
  proc.div( r1, r2, r3, 0);
  proc.mflo( r1, r2, r3, 0);
  BOOST_CHECK( r3.read() == 137/30 );
  proc.mfhi(r1, r2, r3, 0);
  BOOST_CHECK( r3.read() == 137%30 );
  r2 = -40;
  proc.div( r1, r2, r3, 0);
  proc.mflo( r1, r2, r3, 0);
  BOOST_CHECK( r3.read() == Word(137/-40) );
  proc.mfhi( r1, r2, r3, 0);
  BOOST_CHECK( r3.read() == Word(137%-40) );

  // Divide unsigned
  r1 = 2147483705; // 2^31 + 57;
  r2 = 32;
  proc.divu( r1, r2, r3, 0 );
  proc.mflo(r1, r2, r3, 0);
  BOOST_CHECK( r3.read() == 67108865 ); //2^26 + 1
  proc.mfhi( r1, r2, r3, 0 );
  BOOST_CHECK( r3.read() == 25 );

  // Add signed
  r1 = 9182;
  r2 = -1928;
  proc.add( r1, r2, r3, 0);
  BOOST_CHECK( r3.read() == 9182 - 1928 );

  r1 = 1234321;
  proc.dump_reg(r1);

  // Check that data is preserved on a store-load round trip
  r1 = 1234321;
  r2 = 0x34ff50;
  proc.sw(r2,r1,0);
  proc.lw(r2,r3,0);
  BOOST_CHECK( r3.read() == 1234321 );
  // Check that processor initialization worked correctly
  r2 = 4 * sizeof(Word);
  proc.lw( r2, r1, 0);
  BOOST_CHECK( r1.read() == 4 );
}
