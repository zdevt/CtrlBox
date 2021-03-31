/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetWpc.cpp
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

#include "NetCmdSetWpc.h"
#include "OpticEngineInterface.h"

NetCmdSetWpc::NetCmdSetWpc ( )
{
}

NetCmdSetWpc::~NetCmdSetWpc()
{
}

int NetCmdSetWpc::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_wpc_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_wpc_t* pset_wpc = reinterpret_cast<set_wpc_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  GET_ENGPTR->SetWpcMode ( pset_wpc->mode );
  GET_ENGPTR->SetWpcTarget ( reinterpret_cast<uint8_t*> ( & ( pset_wpc->target ) ) );

  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetWpc::GetObj ()
{
  return std::make_shared<NetCmdSetWpc> (  );
}

