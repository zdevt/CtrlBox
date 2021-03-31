/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetBcMode.cpp
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

#include "NetCmdSetBcMode.h"
#include "XmlConfig.h"

NetCmdSetBcMode::NetCmdSetBcMode ( )
{
}

NetCmdSetBcMode::~NetCmdSetBcMode()
{
}

int NetCmdSetBcMode::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_bcmode_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;
  #if !defined(__i386__) && !defined(__x86_64__)
  set_bcmode_t* pset_bcmode = reinterpret_cast<set_bcmode_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  GET_ENGPTR->SetBcMode ( pset_bcmode->bcMode );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetBcMode::GetObj ()
{
  return std::make_shared<NetCmdSetBcMode> (  );
}

