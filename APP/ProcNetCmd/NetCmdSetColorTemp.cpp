/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetColorTemp.cpp
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

#include "NetCmdSetColorTemp.h"
#include "XmlConfig.h"

NetCmdSetColorTemp::NetCmdSetColorTemp ( )
{
}

NetCmdSetColorTemp::~NetCmdSetColorTemp()
{
}

int NetCmdSetColorTemp::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_colortemp_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_colortemp_t* pset_colortemp = reinterpret_cast<set_colortemp_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  int colortempId = ( int ) pset_colortemp->colortempId ;

  #if 0
  std::stringstream ss;
  ss << "COLORTEMP" << colortempId;

  int red, green, blue;

  if ( XmlConfig::GetParam ( ss.str(), "RED", red, 255 )
       && XmlConfig::GetParam ( ss.str(), "GREEN", green, 255 )
       && XmlConfig::GetParam ( ss.str(), "BLUE", blue, 255 )  )
  {
    //TODO:

    XmlConfig::SetParam ( "OPTICENGINE", "COLORTEMPID", colortempId );
  }
  else
    mcp_status.status = 1;

  #endif

  XmlConfig::SetParam ( "OpticEngine", "COLORTEMPID", colortempId );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetColorTemp::GetObj ()
{
  return std::make_shared<NetCmdSetColorTemp> (  );
}

