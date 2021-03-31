/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetDoubleDesktopSwitchMode.cpp
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

#include "NetCmdGetDoubleDesktopSwitchMode.h"

NetCmdGetDoubleDesktopSwitchMode::NetCmdGetDoubleDesktopSwitchMode ( )
{
}

NetCmdGetDoubleDesktopSwitchMode::~NetCmdGetDoubleDesktopSwitchMode()
{
}

int NetCmdGetDoubleDesktopSwitchMode::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_mode_t get_mode;
  #if !defined(__i386__) && !defined(__x86_64__)
  int mode = 0;
  XmlConfig::GetParam ( "DeskTopConf", "DDSwitchMode", mode, int ( 0 ) );
  get_mode.mode = mode;
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_DOUBLEDESKTOP_SWITCHMODE, reinterpret_cast<char*> ( &get_mode ), sizeof ( get_mode ) );
}

std::shared_ptr<NetCmd> NetCmdGetDoubleDesktopSwitchMode::GetObj ()
{
  return std::make_shared<NetCmdGetDoubleDesktopSwitchMode> (  );
}

