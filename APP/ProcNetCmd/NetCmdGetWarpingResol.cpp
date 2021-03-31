/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetWarpingResol.cpp
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

#include "NetCmdGetWarpingResol.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdGetWarpingResol::NetCmdGetWarpingResol ( )
{
}

NetCmdGetWarpingResol::~NetCmdGetWarpingResol()
{
}

int NetCmdGetWarpingResol::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < sizeof ( MCP_HEADER_t ) )
    return 0;

  get_warpingresol_t get_warpingresol;

  #if defined(__arm__)
  Warping787::GetResol ( get_warpingresol.width, get_warpingresol.height );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_WARPINGRESOL, reinterpret_cast<char*> ( &get_warpingresol ), sizeof ( get_warpingresol ) );
}

std::shared_ptr<NetCmd> NetCmdGetWarpingResol::GetObj ()
{
  return std::make_shared<NetCmdGetWarpingResol> (  );
}

