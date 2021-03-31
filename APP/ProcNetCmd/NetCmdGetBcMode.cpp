/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetBcMode.cpp
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

#include "NetCmdGetBcMode.h"
#include "XmlConfig.h"

NetCmdGetBcMode::NetCmdGetBcMode ( )
{
}

NetCmdGetBcMode::~NetCmdGetBcMode()
{
}

int NetCmdGetBcMode::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < sizeof ( MCP_HEADER_t ) )
    return 0;

  get_bcmode_t get_bcmode;
  #if defined(__arm__)
  GET_ENGPTR->GetBcMode ( get_bcmode.bcMode );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_BCMODE, reinterpret_cast<char*> ( &get_bcmode ), sizeof ( get_bcmode ) );
}

std::shared_ptr<NetCmd> NetCmdGetBcMode::GetObj ()
{
  return std::make_shared<NetCmdGetBcMode> (  );
}

