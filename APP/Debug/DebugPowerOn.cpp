/*
 * =====================================================================================
 *
 *       Filename:  DebugPowerOn.cpp
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

#include "DebugPowerOn.h"
#include "PowerOn.h"
#include "LogPrint.h"


DebugPowerOn::DebugPowerOn()
{
}

DebugPowerOn::~DebugPowerOn()
{
}

bool DebugPowerOn::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 1 )
  {
    Help();
    return false;
  }

  uint32_t val = 0;
  std::stringstream ss ( funarg );
  ss >> std::hex >> val;
  PowerOn::SetOnOrOff ( val );

  return true;
}

void DebugPowerOn::Help ( )
{
  PRINT_LOG2 ( "DebugPowerOn 0/1\n" );
}

std::shared_ptr<DebugFun> DebugPowerOn::GetObj ( )
{
  return std::make_shared<DebugPowerOn> ( );
}

