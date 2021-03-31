/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetWarpingData.cpp
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

#include "NetCmdSetWarpingData.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdSetWarpingData::NetCmdSetWarpingData ( )
{
}

NetCmdSetWarpingData::~NetCmdSetWarpingData()
{
}

int NetCmdSetWarpingData::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_warpingdata_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_warpingdata_t* pset_warpingdata = reinterpret_cast<set_warpingdata_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  Warping787::SetWarpingData ( pset_warpingdata->grid, pset_warpingdata->datalen, pset_warpingdata->data );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetWarpingData::GetObj ()
{
  return std::make_shared<NetCmdSetWarpingData> (  );
}

