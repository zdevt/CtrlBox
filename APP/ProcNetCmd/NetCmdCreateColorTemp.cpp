/*
 * =====================================================================================
 *
 *       Filename:  NetCmdCreateColorTemp.cpp
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
#include <sstream>

#include "NetCmdCreateColorTemp.h"
#include "XmlConfig.h"

NetCmdCreateColorTemp::NetCmdCreateColorTemp ( )
{
}

NetCmdCreateColorTemp::~NetCmdCreateColorTemp()
{
}

int NetCmdCreateColorTemp::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( create_color_temp_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  create_color_temp_t* pcreate_color_temp = reinterpret_cast<create_color_temp_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  std::stringstream ss;
  ss << "COLORTEMP" << ( uint16_t ) ( pcreate_color_temp->colortempId );

  #if !defined(__i386__) && !defined(__x86_64__)
  //TODO:
  XmlConfig::SetParam ( ss.str(), "RED", pcreate_color_temp->red );
  XmlConfig::SetParam ( ss.str(), "GREEN", pcreate_color_temp->green );
  XmlConfig::SetParam ( ss.str(), "BLUE",  pcreate_color_temp->blue );

  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdCreateColorTemp::GetObj ()
{
  return std::make_shared<NetCmdCreateColorTemp> (  );
}

