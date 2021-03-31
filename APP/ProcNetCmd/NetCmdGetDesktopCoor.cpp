/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetDesktopCoor.cpp
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

#include "NetCmdGetDesktopCoor.h"
#include "OpticEngineThin.h"

NetCmdGetDesktopCoor::NetCmdGetDesktopCoor (  )
{
}

NetCmdGetDesktopCoor::~NetCmdGetDesktopCoor()
{
}

int NetCmdGetDesktopCoor::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_desktopcoor_t get_desktopcoor;
  #if defined(__arm__)
  int temp = 0;
  XmlConfig::GetParam ( "SignalRect", "x", get_desktopcoor.x, temp );
  XmlConfig::GetParam ( "SignalRect", "y", get_desktopcoor.y, temp );
  XmlConfig::GetParam ( "SignalRect", "w", get_desktopcoor.w, temp );
  XmlConfig::GetParam ( "SignalRect", "h", get_desktopcoor.h, temp );
  #endif

  HandleRsp ( cmd, rsp, MCP_RET_GET_DESKTOPCOOR, reinterpret_cast<char*> ( &get_desktopcoor ), sizeof ( get_desktopcoor ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdGetDesktopCoor::GetObj (  )
{
  return std::make_shared<NetCmdGetDesktopCoor> ( );
}

