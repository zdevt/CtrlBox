/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetBoardState.cpp
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

#include "NetCmdGetBoardState.h"

NetCmdGetBoardState::NetCmdGetBoardState ( )
{
}

NetCmdGetBoardState::~NetCmdGetBoardState()
{
}

int NetCmdGetBoardState::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( get_boardtype_cmd_t ) ) )
    return 0;

  get_boardstate_t get_boardstate;
  #if !defined(__i386__) && !defined(__x86_64__)
  /*  todo  */
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_BOARDSTATE, reinterpret_cast<char*> ( &get_boardstate ), sizeof ( get_boardstate ) );
}

std::shared_ptr<NetCmd> NetCmdGetBoardState::GetObj ()
{
  return std::make_shared<NetCmdGetBoardState> (  );
}

