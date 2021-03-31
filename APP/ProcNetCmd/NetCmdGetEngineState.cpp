/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetEngineState.cpp
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

#include "NetCmdGetEngineState.h"
#include "PowerOn.h"

NetCmdGetEngineState::NetCmdGetEngineState (  )
{
}

NetCmdGetEngineState::~NetCmdGetEngineState()
{
}

int NetCmdGetEngineState::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_engine_state_t get_engine_state;
  #if defined(__arm__)

  if ( PowerOn::GetOnOffFlag( ) )
    get_engine_state.state = 1;
  else
    get_engine_state.state = 0;

  #endif

  HandleRsp ( cmd, rsp, MCP_RET_GET_ENGINESTATE, reinterpret_cast<char*> ( &get_engine_state ), sizeof ( get_engine_state ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdGetEngineState::GetObj (  )
{
  return std::make_shared<NetCmdGetEngineState> ( );
}

