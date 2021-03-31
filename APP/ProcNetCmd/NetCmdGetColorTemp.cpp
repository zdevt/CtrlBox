/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetColorTemp.cpp
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

#include "NetCmdGetColorTemp.h"
#include "XmlConfig.h"

NetCmdGetColorTemp::NetCmdGetColorTemp ( )
{
}

NetCmdGetColorTemp::~NetCmdGetColorTemp()
{
}

int NetCmdGetColorTemp::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < sizeof ( MCP_HEADER_t ) )
    return 0;

  get_colortemp_t get_colortemp;
  #if !defined(__i386__) && !defined(__x86_64__)
  int temp = 0;
  XmlConfig::GetParam ( "OpticEngine", "COLORTEMPID", temp, 0 );
  get_colortemp.colortempId = temp;
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_COLORTEMP, reinterpret_cast<char*> ( &get_colortemp ), sizeof ( get_colortemp ) );
}

std::shared_ptr<NetCmd> NetCmdGetColorTemp::GetObj ()
{
  return std::make_shared<NetCmdGetColorTemp> (  );
}

