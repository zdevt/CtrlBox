/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetWplgCoeff.cpp
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

#include "NetCmdSetWplgCoeff.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdSetWplgCoeff::NetCmdSetWplgCoeff ( )
{
}

NetCmdSetWplgCoeff::~NetCmdSetWplgCoeff()
{
}

int NetCmdSetWplgCoeff::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_wplgcoeff_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_wplgcoeff_t* pset_wplgcoeff = reinterpret_cast<set_wplgcoeff_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  Warping787::SetWplgCoeff ( pset_wplgcoeff->wplg );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetWplgCoeff::GetObj ()
{
  return std::make_shared<NetCmdSetWplgCoeff> (  );
}

