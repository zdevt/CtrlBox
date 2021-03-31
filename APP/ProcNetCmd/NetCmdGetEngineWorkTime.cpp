/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetEngineWorkTime.cpp
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

#include "NetCmdGetEngineWorkTime.h"
#include "OpticEngineInterface.h"

NetCmdGetEngineWorkTime::NetCmdGetEngineWorkTime ( )
{
}

NetCmdGetEngineWorkTime::~NetCmdGetEngineWorkTime()
{
}

int NetCmdGetEngineWorkTime::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_engineworktime_t get_engineworktime;
  #if !defined(__i386__) && !defined(__x86_64__)
  GET_ENGPTR->GetWorkTime ( get_engineworktime.time );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_ENGINEWORKTIME, reinterpret_cast<char*> ( &get_engineworktime ), sizeof ( get_engineworktime ) );
}

std::shared_ptr<NetCmd> NetCmdGetEngineWorkTime::GetObj ()
{
  return std::make_shared<NetCmdGetEngineWorkTime> (  );
}

