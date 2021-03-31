/*
 * =====================================================================================
 *
 *       Filename:  DebugI2cTestGet.cpp
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

#include "DebugI2cTestGet.h"
#include "LogPrint.h"
#include "I2cBusInterface.h"

DebugI2cTestGet::DebugI2cTestGet()
{
}

DebugI2cTestGet::~DebugI2cTestGet()
{
}

bool DebugI2cTestGet::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 5 )
  {
    Help();
    return false;
  }

  std::string filename;
  int busNo, slave, addr, readLen, addrLen;
  std::stringstream ss ( funarg );
  ss >> std::hex >> busNo >> slave >> addr >> addrLen >> readLen;
  std::vector<uint8_t> vechar;
  vechar.resize ( readLen, 0 );

  int ret = I2cBusInterface::Read ( I2cBusInterface::GetBusName ( busNo ), slave, addr, &vechar[0], readLen, addrLen );
  PRINT_LOG2 ( "I2cTestGet ret=%d ", ret );
  PRINT_LOG2 ( "\n" );

  if ( ret > 0 )
  {
    for ( uint32_t i = 0; i < vechar.size(); ++i )
    {
      if ( ( i != 0 ) && ( i % 0x10 == 0 ) )
        PRINT_LOG2 ( "\n" );

      PRINT_LOG2 ( "%02x ", vechar[i] );
    }

    PRINT_LOG2 ( "\n" );
  }

  return true;
}

void DebugI2cTestGet::Help ( )
{
  PRINT_LOG2 ( "I2cTestGet busNo slave addr addrLen readLen \n" );
}

std::shared_ptr<DebugFun> DebugI2cTestGet::GetObj ( )
{
  return std::make_shared<DebugI2cTestGet> ( );
}

