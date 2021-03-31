/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetLutSet.cpp
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

#include "NetCmdSetLutSet.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdSetLutSet::NetCmdSetLutSet ( )
{
}

NetCmdSetLutSet::~NetCmdSetLutSet()
{
}

int NetCmdSetLutSet::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_lut_set_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_lut_set_t* pset_lut_set = reinterpret_cast<set_lut_set_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  Warping787::SetLutSet ( pset_lut_set->set );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetLutSet::GetObj ()
{
  return std::make_shared<NetCmdSetLutSet> (  );
}

