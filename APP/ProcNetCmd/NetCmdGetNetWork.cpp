/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetNetWork.cpp
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

#include "NetCmdGetNetWork.h"
#include "ErrorCode.h"
#include "GetNetWork.h"


NetCmdGetNetWork::NetCmdGetNetWork ( )
{
}

NetCmdGetNetWork::~NetCmdGetNetWork()
{
}

int NetCmdGetNetWork::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_network_t get_network;
  #if !defined(__i386__) && !defined(__x86_64__)
  std::string ip, mask, mac, gw;
  memset ( &get_network, 0, sizeof ( get_network ) );
  GetNetWork::GetIp ( ip, mask );
  memcpy ( get_network.ip, ip.c_str(), ip.size() );
  memcpy ( get_network.mask, mask.c_str(), mask.size() );

  GetNetWork::GetMac ( mac );
  memcpy ( get_network.mac, mac.c_str(), mac.size() );

  GetNetWork::GetGateWay ( gw );
  memcpy ( get_network.gw, gw.c_str(), gw.size() );
  #endif
  return HandleRsp ( cmd, rsp, MCP_RET_GET_NETWORK, reinterpret_cast<char*> ( &get_network ), sizeof ( get_network ) );
}

std::shared_ptr<NetCmd> NetCmdGetNetWork::GetObj ()
{
  return std::make_shared<NetCmdGetNetWork> (  );
}

