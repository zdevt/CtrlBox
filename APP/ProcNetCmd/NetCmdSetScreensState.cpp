/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetScreensState.cpp
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

#include "NetCmdSetScreensState.h"
#include "GpioPwm.h"

NetCmdSetScreensState::NetCmdSetScreensState (  )
{
}

NetCmdSetScreensState::~NetCmdSetScreensState()
{
}

int NetCmdSetScreensState::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_screens_state_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_screens_state_t* pset_screens_state = reinterpret_cast<set_screens_state_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  if ( pset_screens_state->state == 1 )
  {
    GET_GPIOPWM->Start();
  }
  else if ( pset_screens_state->state == 2 )
  {
    GET_GPIOPWM->Out();
  }
  else if ( pset_screens_state->state == 3 )
  {
    GET_GPIOPWM->In();
  }
  else if ( pset_screens_state->state == 0 )
  {
    GET_GPIOPWM->Stop();
  }

  #endif

  HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdSetScreensState::GetObj (  )
{
  return std::make_shared<NetCmdSetScreensState> ();
}

