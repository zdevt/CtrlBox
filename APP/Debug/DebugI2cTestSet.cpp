/*
 * =====================================================================================
 *
 *       Filename:  DebugI2cTestSet.cpp
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

#include "DebugI2cTestSet.h"
#include "LogPrint.h"
#include "I2cBusInterface.h"

DebugI2cTestSet::DebugI2cTestSet()
{
}

DebugI2cTestSet::~DebugI2cTestSet()
{
}

bool DebugI2cTestSet::Fun ( std::string funarg )
{
  uint32_t argNum = GetArgNum ( funarg );

  if ( argNum <= 4 )
  {
    Help();
    return false;
  }

  std::string filename;
  int busNo, slave, addr, addrLen ;
  std::stringstream ss ( funarg );
  ss >> std::hex >> busNo >> slave >> addr >> addrLen;

  std::vector<uint8_t> vechar;
  uint32_t temp = 0;

  for ( uint32_t i = 0; i < argNum - 4; ++i )
  {
    ss >> std::hex >> temp;
    vechar.push_back ( ( uint8_t ) temp );
  }

  int ret = I2cBusInterface::Write ( I2cBusInterface::GetBusName ( busNo ), slave, addr, &vechar[0], vechar.size(), addrLen );
  PRINT_LOG2 ( "I2cTestSet ret=%d\n", ret );

  return true;
}

void DebugI2cTestSet::Help ( )
{
  PRINT_LOG2 ( "I2cTestSet busNo slave addr addrLen data0 .... datan \n" );
}

std::shared_ptr<DebugFun> DebugI2cTestSet::GetObj ( )
{
  return std::make_shared<DebugI2cTestSet> ( );
}

