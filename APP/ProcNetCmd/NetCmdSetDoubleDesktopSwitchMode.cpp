/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDoubleDesktopSwitchMode.cpp
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

#include "NetCmdSetDoubleDesktopSwitchMode.h"
#include "FpgaImageLogoAndDrgb.h"

NetCmdSetDoubleDesktopSwitchMode::NetCmdSetDoubleDesktopSwitchMode ( )
{
}

NetCmdSetDoubleDesktopSwitchMode::~NetCmdSetDoubleDesktopSwitchMode()
{
}

int NetCmdSetDoubleDesktopSwitchMode::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_mode_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;
  #if defined(__arm__)
  set_mode_t* pset_mode = reinterpret_cast<set_mode_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  XmlConfig::SetParam ( "DeskTopConf", "DDSwitchMode", int ( pset_mode->mode ) );
  FpgaImageLogoAndDrgb::SetDoubleDesktopSwithMode ( pset_mode->mode );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetDoubleDesktopSwitchMode::GetObj ()
{
  return std::make_shared<NetCmdSetDoubleDesktopSwitchMode> (  );
}

