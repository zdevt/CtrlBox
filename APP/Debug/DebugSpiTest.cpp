/*
 * =====================================================================================
 *
 *       Filename:  DebugSpiTest.cpp
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

#include "DebugSpiTest.h"
#include "LogPrint.h"
#include "SpiBusInterface.h"

DebugSpiTest::DebugSpiTest()
{
}

DebugSpiTest::~DebugSpiTest()
{
}

bool DebugSpiTest::Fun ( std::string funarg )
{
  uint32_t argNum = GetArgNum ( funarg );

  if ( argNum < 2 )
  {
    Help();
    return false;
  }

  std::string devname;
  std::stringstream ss ( funarg );
  ss >> devname;

  std::vector<uint8_t> vechar;
  uint32_t temp = 0;

  for ( uint32_t i = 0; i < argNum - 1; ++i )
  {
    ss >> std::hex >> temp;
    vechar.push_back ( ( uint8_t ) temp );
  }

  std::vector<uint8_t> vecharRead;
  vecharRead.resize ( vechar.size(), 0 );

  int ret = SpiBusInterface::RW ( &vechar[0], &vecharRead[0], vechar.size(), devname );

  if ( ret > 0 )
  {
    for ( uint32_t i = 0; i < vecharRead.size(); ++i )
    {
      if ( ( i != 0 ) && ( i % 0x10 == 0 ) )
        PRINT_LOG2 ( "\n" );

      PRINT_LOG2 ( "%02x ", vecharRead[i] );
    }

    PRINT_LOG2 ( "\n" );
  }


  return true;
}

void DebugSpiTest::Help ( )
{
  PRINT_LOG2 ( "SpiTestSet busName wdata0 .... wdatan \n" );
}

std::shared_ptr<DebugFun> DebugSpiTest::GetObj ( )
{
  return std::make_shared<DebugSpiTest> ( );
}

