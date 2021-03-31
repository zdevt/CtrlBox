/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetMonitorOpt.cpp
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

#include "NetCmdGetMonitorOpt.h"

NetCmdGetMonitorOpt::NetCmdGetMonitorOpt (  )
{
}

NetCmdGetMonitorOpt::~NetCmdGetMonitorOpt()
{
}

int NetCmdGetMonitorOpt::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  PRINT_LOG ( LOG_LEVEL_NORMAL, "\n" );

  get_monitor_opt_t get_monitor_opt;
  #if !defined(__i386__) && !defined(__x86_64__)
  /*  TODO  */
  XmlConfig::GetParam ( "OpticEngine", "MonitorOpt", get_monitor_opt.monitorOpt, ( uint32_t ) 0 );
  #endif

  HandleRsp ( cmd, rsp, MCP_RET_GET_MONITOROPT, reinterpret_cast<char*> ( &get_monitor_opt ), sizeof ( get_monitor_opt ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdGetMonitorOpt::GetObj (  )
{
  return std::make_shared<NetCmdGetMonitorOpt> ();
}

