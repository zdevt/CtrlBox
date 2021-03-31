/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetBoardState.cpp
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

#include "NetCmdSetBoardState.h"

NetCmdSetBoardState::NetCmdSetBoardState (  )
{
}

NetCmdSetBoardState::~NetCmdSetBoardState()
{
}

int NetCmdSetBoardState::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_board_state_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if !defined(__i386__) && !defined(__x86_64__)
  set_board_state_t* pset_board_state = reinterpret_cast<set_board_state_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  if ( pset_board_state->boardType ==  0 )
  {
    if ( pset_board_state->state ==  1 )
      system ( "reboot" );
  }

  #endif
  HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdSetBoardState::GetObj (  )
{
  return std::make_shared<NetCmdSetBoardState> ();
}

