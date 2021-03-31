/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetWarpingOnlineState.cpp
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

#include "NetCmdGetWarpingOnlineState.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdGetWarpingOnlineState::NetCmdGetWarpingOnlineState ( )
{
}

NetCmdGetWarpingOnlineState::~NetCmdGetWarpingOnlineState()
{
}

int NetCmdGetWarpingOnlineState::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < sizeof ( MCP_HEADER_t ) )
    return 0;

  get_warpingonlinestate_t get_warpingonlinestate;

  #if defined(__arm__)
  Warping787::GetOnline ( NULL );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_WARPINGONLINESTATE, reinterpret_cast<char*> ( &get_warpingonlinestate ), sizeof ( get_warpingonlinestate ) );
}

std::shared_ptr<NetCmd> NetCmdGetWarpingOnlineState::GetObj ()
{
  return std::make_shared<NetCmdGetWarpingOnlineState> (  );
}

