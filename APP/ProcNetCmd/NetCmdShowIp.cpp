/*
 * =====================================================================================
 *
 *       Filename:  NetCmdShowIp.cpp
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

#include "NetCmdShowIp.h"
#include "ShowIpBmp.h"

NetCmdShowIp::NetCmdShowIp (  )
{
}

NetCmdShowIp::~NetCmdShowIp()
{
}

int NetCmdShowIp::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( show_ip_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  show_ip_t* pshow_ip = reinterpret_cast<show_ip_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  if ( 0 == pshow_ip->flag )
    ShowIpBmp::Off();
  else
    ShowIpBmp::On();

  #endif

  HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdShowIp::GetObj (  )
{
  return std::make_shared<NetCmdShowIp> ();
}

