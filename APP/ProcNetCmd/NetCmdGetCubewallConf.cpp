/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetCubewallConf.cpp
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

#include "NetCmdGetCubewallConf.h"
#include "XmlConfig.h"

NetCmdGetCubewallConf::NetCmdGetCubewallConf ( )
{
}

NetCmdGetCubewallConf::~NetCmdGetCubewallConf()
{
}

int NetCmdGetCubewallConf::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < sizeof ( MCP_HEADER_t ) )
    return 0;

  get_cubewall_conf_t get_cubewall_conf;
  get_cubewall_conf.id = 1;
  get_cubewall_conf.wallRows = 1;
  get_cubewall_conf.wallCols = 1;
  get_cubewall_conf.cubeID = 0;

  #if defined(__arm__)
  uint32_t temp = 0;
  XmlConfig::GetParam ( "CubeWallConf", "ID", temp, 0u );
  get_cubewall_conf.id = temp;

  XmlConfig::GetParam ( "CubeWallConf", "WALLROWS", temp, 1u );
  get_cubewall_conf.wallRows = temp;

  XmlConfig::GetParam ( "CubeWallConf", "WALLCols", temp, 1u );
  get_cubewall_conf.wallCols = temp;

  XmlConfig::GetParam ( "CubeWallConf", "CUBEID", temp, 0u );
  get_cubewall_conf.cubeID = temp;
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_CUBEWALLCONF, reinterpret_cast<char*> ( &get_cubewall_conf ), sizeof ( get_cubewall_conf ) );
}

std::shared_ptr<NetCmd> NetCmdGetCubewallConf::GetObj ()
{
  return std::make_shared<NetCmdGetCubewallConf> (  );
}

