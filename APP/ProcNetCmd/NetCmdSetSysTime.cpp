/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetSysTime.cpp
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
#include <sstream>


#include "NetCmdSetSysTime.h"
#include "ErrorCode.h"
#include "SetNetWork.h"


NetCmdSetSysTime::NetCmdSetSysTime ( )
{
}

NetCmdSetSysTime::~NetCmdSetSysTime()
{
}

int NetCmdSetSysTime::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_systime_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;
  #if !defined(__i386__) && !defined(__x86_64__)
  set_systime_t* pset_systime = reinterpret_cast<set_systime_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  std::stringstream ss;
  ss << pset_systime->year << "-"
     << pset_systime->month << "-"
     << pset_systime->day << " "
     << pset_systime->hour << "-"
     << pset_systime->minute << "-"
     << pset_systime->second;

  std::string setTimeStr = "date -s \"";
  setTimeStr += ss.str();
  setTimeStr += "\";hwclock -w";

  system ( setTimeStr.c_str() );

  #endif
  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetSysTime::GetObj ()
{
  return std::make_shared<NetCmdSetSysTime> (  );
}

