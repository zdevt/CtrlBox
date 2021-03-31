/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetMonitorWarn.cpp
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

#include "NetCmdSetMonitorWarn.h"

NetCmdSetMonitorWarn::NetCmdSetMonitorWarn (  )
{
}

NetCmdSetMonitorWarn::~NetCmdSetMonitorWarn()
{
}

int NetCmdSetMonitorWarn::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_monitor_warn_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if !defined(__i386__) && !defined(__x86_64__)
  /* TODO */
  set_monitor_warn_t* pset_monitor_warn = reinterpret_cast<set_monitor_warn_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  XmlConfig::SetParam ( "OpticEngine", "MonitorWarnOpt", pset_monitor_warn->monitorOpt );
  #endif

  HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdSetMonitorWarn::GetObj (  )
{
  return std::make_shared<NetCmdSetMonitorWarn> ();
}

