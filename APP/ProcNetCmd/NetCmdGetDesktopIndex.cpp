/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetDesktopIndex.cpp
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

#include "NetCmdGetDesktopIndex.h"
#include "FpgaImageSwitch.h"

NetCmdGetDesktopIndex::NetCmdGetDesktopIndex ( )
{
}

NetCmdGetDesktopIndex::~NetCmdGetDesktopIndex()
{
}

int NetCmdGetDesktopIndex::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_desktop_index_t get_desktop_index;

  #if defined(__arm__)
  get_desktop_index.desktopIndex = FpgaImageSwitch::GetDeskTopIndex();
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_DESKTOPINDEX, reinterpret_cast<char*> ( &get_desktop_index ), sizeof ( get_desktop_index ) );
}

std::shared_ptr<NetCmd> NetCmdGetDesktopIndex::GetObj ()
{
  return std::make_shared<NetCmdGetDesktopIndex> (  );
}

