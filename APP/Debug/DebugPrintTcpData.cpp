/*
 * =====================================================================================
 *
 *       Filename:  DebugPrintTcpData.cpp
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

#include "DebugPrintTcpData.h"
#include "LogPrint.h"
#include "TcpHandleConfig.h"

DebugPrintTcpData::DebugPrintTcpData()
{
}

DebugPrintTcpData::~DebugPrintTcpData()
{
}

bool DebugPrintTcpData::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 1 )
  {
    Help();
    return false;
  }

  int flag = 0;
  std::stringstream ss ( funarg );
  ss >> std::hex >> flag;

  if ( 1 == flag )
    TcpHandleConfig::SetShowTcpDataFlag ( true );
  else
    TcpHandleConfig::SetShowTcpDataFlag ( false );

  return true;
}

void DebugPrintTcpData::Help ( )
{
  PRINT_LOG2 ( "PrintTcpData 0/1\n" );
}

std::shared_ptr<DebugFun> DebugPrintTcpData::GetObj ( )
{
  return std::make_shared<DebugPrintTcpData> ( );
}

