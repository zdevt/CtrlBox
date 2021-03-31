/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDutyCycle.cpp
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

#include "NetCmdSetDutyCycle.h"

NetCmdSetDutyCycle::NetCmdSetDutyCycle ( )
{
}

NetCmdSetDutyCycle::~NetCmdSetDutyCycle()
{
}

int NetCmdSetDutyCycle::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_dc_index_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;
  #if defined(__arm__)
  set_dc_index_t* pset_dc_index = reinterpret_cast<set_dc_index_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  GET_ENGPTR->SetDutycycle ( pset_dc_index->dcIndex );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetDutyCycle::GetObj ()
{
  return std::make_shared<NetCmdSetDutyCycle> (  );
}

