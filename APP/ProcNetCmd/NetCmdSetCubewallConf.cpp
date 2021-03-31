/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetCubewallConf.cpp
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

#include "NetCmdSetCubewallConf.h"
#include "XmlConfig.h"

NetCmdSetCubewallConf::NetCmdSetCubewallConf ( )
{
}

NetCmdSetCubewallConf::~NetCmdSetCubewallConf()
{
}

int NetCmdSetCubewallConf::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_cubewall_conf_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;
  #if !defined(__i386__) && !defined(__x86_64__)
  set_cubewall_conf_t* pset_cubewall_conf = reinterpret_cast<set_cubewall_conf_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  XmlConfig::SetParam ( "CubeWallConf", "ID", ( int ) pset_cubewall_conf->id );
  XmlConfig::SetParam ( "CubeWallConf", "WALLROWS", pset_cubewall_conf->wallRows );
  XmlConfig::SetParam ( "CubeWallConf", "WALLCols", pset_cubewall_conf->wallCols );
  XmlConfig::SetParam ( "CubeWallConf", "CUBEID", pset_cubewall_conf->cubeID );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetCubewallConf::GetObj ()
{
  return std::make_shared<NetCmdSetCubewallConf> (  );
}

