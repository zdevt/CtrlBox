/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetMonitorWarn.cpp
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

#include "NetCmdGetMonitorWarn.h"

NetCmdGetMonitorWarn::NetCmdGetMonitorWarn (  )
{
}

NetCmdGetMonitorWarn::~NetCmdGetMonitorWarn()
{
}

int NetCmdGetMonitorWarn::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( get_monitor_warn_cmd_t ) ) )
    return 0;

  get_monitor_warn_t get_monitor_warn;

  #if !defined(__i386__) && !defined(__x86_64__)
  /* TODO */
  get_monitor_warn_cmd_t* pget_monitor_warn_cmd = reinterpret_cast<get_monitor_warn_cmd_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  if ( pget_monitor_warn_cmd->monitorOpt == 0 )
  {

  }

  #endif

  HandleRsp ( cmd, rsp, MCP_RET_GET_MONITORWARN, reinterpret_cast<char*> ( &get_monitor_warn ), sizeof ( get_monitor_warn ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdGetMonitorWarn::GetObj (  )
{
  return std::make_shared<NetCmdGetMonitorWarn> ();
}

