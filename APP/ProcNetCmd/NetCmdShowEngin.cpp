/*
 * =====================================================================================
 *
 *       Filename:  NetCmdShowEngin.cpp
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

#include "NetCmdShowEngin.h"

NetCmdShowEngin::NetCmdShowEngin ( )
{
}

NetCmdShowEngin::~NetCmdShowEngin()
{
}

int NetCmdShowEngin::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t )  ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if !defined(__i386__) && !defined(__x86_64__)
  //TODO:

  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdShowEngin::GetObj ()
{
  return std::make_shared<NetCmdShowEngin> (  );
}

