/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetUsePeriodEnable.cpp
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

#include "NetCmdSetUsePeriodEnable.h"
#include "XmlConfig.h"
#include "OpticEngineInterface.h"

NetCmdSetUsePeriodEnable::NetCmdSetUsePeriodEnable ( )
{
}

NetCmdSetUsePeriodEnable::~NetCmdSetUsePeriodEnable()
{
}

int NetCmdSetUsePeriodEnable::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_use_period_enable_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;
  #if !defined(__i386__) && !defined(__x86_64__)
  set_use_period_enable_t* pset_use_period_enable = reinterpret_cast<set_use_period_enable_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  GET_ENGPTR->SetUsePeriodEnable ( pset_use_period_enable->enable );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetUsePeriodEnable::GetObj ()
{
  return std::make_shared<NetCmdSetUsePeriodEnable> (  );
}

