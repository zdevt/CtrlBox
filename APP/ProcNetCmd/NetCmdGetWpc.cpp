/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetWpc.cpp
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

#include "NetCmdGetWpc.h"
#include "OpticEngineInterface.h"

NetCmdGetWpc::NetCmdGetWpc ( )
{
}

NetCmdGetWpc::~NetCmdGetWpc()
{
}

int NetCmdGetWpc::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_wpc_t get_wpc;
  #if defined(__arm__)
  GET_ENGPTR->GetWpcMode ( get_wpc.mode );
  GET_ENGPTR->GetWpcTarget ( reinterpret_cast<uint8_t*> ( & ( get_wpc.target ) ) );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_WPC, reinterpret_cast<char*> ( &get_wpc ), sizeof ( get_wpc ) );
}

std::shared_ptr<NetCmd> NetCmdGetWpc::GetObj ()
{
  return std::make_shared<NetCmdGetWpc> (  );
}

