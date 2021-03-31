/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetUniformityCorrectionSelPos.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/10/2017 11:00:22 AM
 *  Last Modified:  08/10/2017 11:00:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */


#include <string>

#include "NetCmdSetUniformityCorrectionSelPos.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdSetUniformityCorrectionSelPos::NetCmdSetUniformityCorrectionSelPos ( )
{
}

NetCmdSetUniformityCorrectionSelPos::~NetCmdSetUniformityCorrectionSelPos()
{
}

int NetCmdSetUniformityCorrectionSelPos::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_ucselpos_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_ucselpos_t* pset_ucselpos = reinterpret_cast<set_ucselpos_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  Warping787::UCSelectPos ( pset_ucselpos->x, pset_ucselpos->y );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetUniformityCorrectionSelPos::GetObj ()
{
  return std::make_shared<NetCmdSetUniformityCorrectionSelPos> (  );
}

