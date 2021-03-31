/*
 * =====================================================================================
 *
 *       Filename:  DebugGpioGet.cpp
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

#include "DebugGpioGet.h"
#include "LogPrint.h"
#include "At91GpioDev.h"

DebugGpioGet::DebugGpioGet()
{
}

DebugGpioGet::~DebugGpioGet()
{
}

bool DebugGpioGet::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 1 )
  {
    Help();
    return false;
  }

  std::string pinName;
  uint32_t val = 1;
  std::stringstream ss ( funarg );
  ss >> pinName;

  AT91SetGpioInput ( At91GetPinByName ( pinName ), val );
  val = At91GetGpioValue ( At91GetPinByName ( pinName ) );
  PRINT_LOG2 ( "GpioGet %s = %d\n", pinName.c_str(), val );
  return true;
}

void DebugGpioGet::Help ( )
{
  PRINT_LOG2 ( "GpioGet PA0\n" );
}

std::shared_ptr<DebugFun> DebugGpioGet::GetObj ( )
{
  return std::make_shared<DebugGpioGet> ( );
}

