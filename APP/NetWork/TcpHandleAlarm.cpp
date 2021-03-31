/*
 * =====================================================================================
 *
 *       Filename:  TcpHandleAlarm.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/21/2014 10:14:14 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   zt(),
 *        Company:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>

#include "TcpHandleAlarm.h"
#include "UpgradeFileInterface.h"

std::shared_ptr<TcpHandle> TcpHandleAlarm::GetObj ( )
{
  return std::make_shared<TcpHandleAlarm> ();
}

TcpHandleAlarm::TcpHandleAlarm ( )
{
}

TcpHandleAlarm::~TcpHandleAlarm()
{

}

int TcpHandleAlarm::ProcCmd ( int fd, char* buffer, int len )
{
  return 0;
}

