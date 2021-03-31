/*
 * =====================================================================================
 *
 *       Filename:  DebugIpconfig.cpp
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

#include "DebugIpconfig.h"
#include "SetNetWork.h"
#include "LogPrint.h"

DebugIpconfig::DebugIpconfig()
{
}

DebugIpconfig::~DebugIpconfig()
{
}

bool DebugIpconfig::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 2 )
  {
    Help();
    return false;
  }

  std::string ip, mask;
  std::stringstream ss ( funarg );
  ss >> ip >> mask;
  SetNetWork::SetIp ( ip, mask );

  return true;
}

void DebugIpconfig::Help ( )
{
  PRINT_LOG2 ( "Ipconfig ip mask\n" );
}

std::shared_ptr<DebugFun> DebugIpconfig::GetObj ( )
{
  return std::make_shared<DebugIpconfig> ( );
}


