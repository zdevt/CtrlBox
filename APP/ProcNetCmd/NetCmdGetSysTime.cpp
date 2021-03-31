/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetSysTime.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/06/2015 03:13:23 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <string>
#include <time.h>


#include "NetCmdGetSysTime.h"


NetCmdGetSysTime::NetCmdGetSysTime ( )
{
}

NetCmdGetSysTime::~NetCmdGetSysTime()
{
}

int NetCmdGetSysTime::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() <  sizeof ( MCP_HEADER_t ) )
    return 0;

  get_systime_t get_systime;

  time_t timeNow = time ( NULL );
  tm tmNow;
  localtime_r ( &timeNow, &tmNow );

  get_systime.year      = tmNow.tm_year + 1900;
  get_systime.month     = tmNow.tm_mon + 1;
  get_systime.day       = tmNow.tm_mday;
  get_systime.hour      = tmNow.tm_hour;
  get_systime.minute    = tmNow.tm_min;
  get_systime.second    = tmNow.tm_sec;

  return HandleRsp ( cmd, rsp, MCP_RET_GET_SYSTIME, reinterpret_cast<char*> ( &get_systime ), sizeof ( get_systime ) );
}

std::shared_ptr<NetCmd> NetCmdGetSysTime::GetObj ()
{
  return std::make_shared<NetCmdGetSysTime> (  );
}

