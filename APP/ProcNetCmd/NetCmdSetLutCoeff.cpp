/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetLutCoeff.cpp
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

#include "NetCmdSetLutCoeff.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdSetLutCoeff::NetCmdSetLutCoeff ( )
{
}

NetCmdSetLutCoeff::~NetCmdSetLutCoeff()
{
}

int NetCmdSetLutCoeff::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_lutcoeff_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_lutcoeff_t* pset_lutcoeff = reinterpret_cast<set_lutcoeff_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  Warping787::SetLutCoeff ( pset_lutcoeff->hlut, pset_lutcoeff->vlut );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetLutCoeff::GetObj ()
{
  return std::make_shared<NetCmdSetLutCoeff> (  );
}

