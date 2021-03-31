/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetWarpingCoor.cpp
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

#include "NetCmdSetWarpingCoor.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdSetWarpingCoor::NetCmdSetWarpingCoor ( )
{
}

NetCmdSetWarpingCoor::~NetCmdSetWarpingCoor()
{
}

int NetCmdSetWarpingCoor::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( MCP_WARPINGCOOR_T ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  MCP_WARPINGCOOR_T* pMCP_WARPINGCOOR =
    reinterpret_cast<MCP_WARPINGCOOR_T*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  Warping787::SetWarpingCoor ( reinterpret_cast<void*> ( pMCP_WARPINGCOOR ) );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetWarpingCoor::GetObj ()
{
  return std::make_shared<NetCmdSetWarpingCoor> (  );
}

