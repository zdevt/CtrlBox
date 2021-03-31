/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetNetWork.cpp
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
#include <string.h>
#include <strings.h>


#include "NetCmdSetNetWork.h"
#include "SetNetWork.h"


NetCmdSetNetWork::NetCmdSetNetWork ( )
{
}

NetCmdSetNetWork::~NetCmdSetNetWork()
{
}

int NetCmdSetNetWork::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_network_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if !defined(__i386__) && !defined(__x86_64__)
  set_network_t* pset_network = reinterpret_cast<set_network_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  if ( strlen ( ( char* ) ( pset_network->mac ) ) )
  {
    SetNetWork::SetMac ( ( char* ) ( pset_network->mac ) );
  }

  SetNetWork::SetIp ( ( char* ) ( pset_network->ip ), ( char* ) ( pset_network->mask ) );
  SetNetWork::SetGateWay ( ( char* ) ( pset_network->gw ) );
  PRINT_LOG ( LOG_LEVEL_NORMAL, "Set network done!\n" );
  #endif
  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetNetWork::GetObj ()
{
  return std::make_shared<NetCmdSetNetWork> (  );
}

