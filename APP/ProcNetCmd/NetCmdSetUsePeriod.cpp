/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetUsePeriod.cpp
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

#include "NetCmdSetUsePeriod.h"
#include "XmlConfig.h"
#include "OpticEngineInterface.h"

NetCmdSetUsePeriod::NetCmdSetUsePeriod ( )
{
}

NetCmdSetUsePeriod::~NetCmdSetUsePeriod()
{
}

int NetCmdSetUsePeriod::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_user_period_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;
  #if !defined(__i386__) && !defined(__x86_64__)
  set_user_period_t* pset_user_period = reinterpret_cast<set_user_period_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  GET_ENGPTR->SetUsePeriod ( pset_user_period->useperiodInSec );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetUsePeriod::GetObj ()
{
  return std::make_shared<NetCmdSetUsePeriod> (  );
}

