/*
 * =====================================================================================
 *
 *       Filename:  DebugSetMac.cpp
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

#include "DebugSetMac.h"
#include "SetNetWork.h"
#include "LogPrint.h"

DebugSetMac::DebugSetMac()
{
}

DebugSetMac::~DebugSetMac()
{
}

bool DebugSetMac::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 1 )
  {
    Help();
    return false;
  }

  std::string mac;
  std::stringstream ss ( funarg );
  ss >> mac;
  SetNetWork::SetMac ( mac );
  return true;
}

void DebugSetMac::Help ( )
{
  PRINT_LOG2 ( "SetMac mac\n" );
}

std::shared_ptr<DebugFun> DebugSetMac::GetObj ( )
{
  return std::make_shared<DebugSetMac> ( );
}


