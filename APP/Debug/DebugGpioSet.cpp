/*
 * =====================================================================================
 *
 *       Filename:  DebugGpioSet.cpp
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

#include "DebugGpioSet.h"
#include "LogPrint.h"
#include "At91GpioDev.h"

DebugGpioSet::DebugGpioSet()
{
}

DebugGpioSet::~DebugGpioSet()
{
}

bool DebugGpioSet::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 2 )
  {
    Help();
    return false;
  }

  std::string pinName;
  uint32_t val = 0;
  std::stringstream ss ( funarg );
  ss >> pinName >> val ;

  AT91SetGpioOutput ( At91GetPinByName ( pinName ), val );

  return true;
}

void DebugGpioSet::Help ( )
{
  PRINT_LOG2 ( "GpioSet PA0 1\n" );
}

std::shared_ptr<DebugFun> DebugGpioSet::GetObj ( )
{
  return std::make_shared<DebugGpioSet> ( );
}

