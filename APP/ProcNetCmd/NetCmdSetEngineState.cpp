/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetEngineState.cpp
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

#include "NetCmdSetEngineState.h"
#include "PowerOn.h"

NetCmdSetEngineState::NetCmdSetEngineState (  )
{
}

NetCmdSetEngineState::~NetCmdSetEngineState()
{
}

int NetCmdSetEngineState::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_engine_state_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_engine_state_t* pset_engine_state = reinterpret_cast<set_engine_state_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  PowerOn::SetOnOrOff ( pset_engine_state->state );
  #endif

  HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdSetEngineState::GetObj (  )
{
  return std::make_shared<NetCmdSetEngineState> ();
}

