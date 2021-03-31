/*
 * =====================================================================================
 *
 *       Filename:  DebugFunTest.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2015 10:45:00 AM CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <unistd.h>

#include "DebugFunTest.h"
#include "FunTest.h"
#include "LogPrint.h"
#include "At91GpioDev.h"
#include "FpgaDev.h"
#include "I2cBusInterface.h"

DebugFunTest::DebugFunTest()
{
}

DebugFunTest::~DebugFunTest()
{
}

bool DebugFunTest::Fun ( std::string funarg )
{
  #if 0
  int a = 0;
  int b = 0;
  int c = 0;
  std::stringstream ss ( funarg );
  ss >> std::hex >> a >> b;
  c = FunTest ( a, b );

  PRINT_LOG2 ( "%s\n", funarg.c_str() );
  PRINT_LOG2 ( "%d+%d=%d\n", a, b, c );
  #endif

  Test();

  return true;
}

void DebugFunTest::Help ( )
{
  PRINT_LOG2 ( "FunTest a b\n" );
}

std::shared_ptr<DebugFun> DebugFunTest::GetObj ( )
{
  return std::make_shared<DebugFunTest> ( );
}

void DebugFunTest::Test()
{
  At91GpioDev::SetGpioOutput ( AT91_PIN_PB22, 0 );
  At91GpioDev::SetGpioOutput ( AT91_PIN_PC27, 0 );

  At91GpioDev::SetGpioOutput ( AT91_PIN_PB27, 0 );
  At91GpioDev::SetGpioOutput ( AT91_PIN_PD9, 0 );

  At91GpioDev::SetGpioOutput ( AT91_PIN_PD9, 1 );
  usleep ( 1000 );
  At91GpioDev::SetGpioOutput ( AT91_PIN_PB27, 0 );
  usleep ( 1000 );
  At91GpioDev::SetGpioOutput ( AT91_PIN_PB27, 1 );
  usleep ( 1000 );
  At91GpioDev::SetGpioOutput ( AT91_PIN_PB27, 0 );

  usleep ( 1000 );
  FpgaSetReg ( 0x80, 0x8070 );
  FpgaSetReg ( 0x81, 0x8003 );
  FpgaSetReg ( 0x82, 0x0698 );
  FpgaSetReg ( 0x83, 0x042a );
  FpgaSetReg ( 0x84, 0x00f0 );
  FpgaSetReg ( 0x85, 0x0668 );
  FpgaSetReg ( 0x86, 0x000e );
  FpgaSetReg ( 0x87, 0x0428 );

  std::vector<unsigned char> vecSend, vecRecv;
  vecRecv.resize ( 2, 0 );
  vecSend.push_back ( 0x5e );
  vecSend.push_back ( 0x91 );
  vecSend.push_back ( 0 );
  vecSend.resize ( 7, 0 );
  vecSend.push_back ( 0x0f );
  vecSend.push_back ( 0x00 );

  for ( int i = 0; i < 0xff; )
  {
    i += 0xf;
    vecSend[8] = i;
    I2cBusInterface::Read ( "/dev/i2c-1", 0x34, 0x0, &vecRecv[0], vecRecv.size(), 0x0 );
    I2cBusInterface::Write ( "/dev/i2c-1", 0x34, 0x0, &vecSend[0], vecSend.size(), 0x0 );
    I2cBusInterface::Read ( "/dev/i2c-1", 0x34, 0x0, &vecRecv[0], vecRecv.size(), 0x0 );
    sleep ( 1 );
  }

}

