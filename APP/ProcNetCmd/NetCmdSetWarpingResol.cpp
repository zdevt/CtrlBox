/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetWarpingResol.cpp
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

#include "NetCmdSetWarpingResol.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdSetWarpingResol::NetCmdSetWarpingResol ( )
{
}

NetCmdSetWarpingResol::~NetCmdSetWarpingResol()
{
}

int NetCmdSetWarpingResol::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_warpingresol_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_warpingresol_t* pset_warpingresol = reinterpret_cast<set_warpingresol_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  Warping787::SetResol ( pset_warpingresol->width, pset_warpingresol->height );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetWarpingResol::GetObj ()
{
  return std::make_shared<NetCmdSetWarpingResol> (  );
}

