/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetMonitorOpt.cpp
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

#include "NetCmdSetMonitorOpt.h"

NetCmdSetMonitorOpt::NetCmdSetMonitorOpt (  )
{
}

NetCmdSetMonitorOpt::~NetCmdSetMonitorOpt()
{
}

int NetCmdSetMonitorOpt::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_monitor_opt_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;
  #if !defined(__i386__) && !defined(__x86_64__)
  /* TODO */
  set_monitor_opt_t* pset_monitor_opt = reinterpret_cast<set_monitor_opt_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  XmlConfig::SetParam ( "OpticEngine", "MonitorOpt", pset_monitor_opt->monitorOpt );
  #endif

  HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdSetMonitorOpt::GetObj (  )
{
  return std::make_shared<NetCmdSetMonitorOpt> ();
}

