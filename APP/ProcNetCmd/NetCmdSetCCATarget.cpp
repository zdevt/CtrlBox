/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetCCATarget.cpp
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

#include "NetCmdSetCCATarget.h"
#include "OpticEngineInterface.h"

NetCmdSetCCATarget::NetCmdSetCCATarget ( )
{
}

NetCmdSetCCATarget::~NetCmdSetCCATarget()
{
}

int NetCmdSetCCATarget::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_cca_target_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_cca_target_t* pset_cca_target = reinterpret_cast<set_cca_target_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  GET_ENGPTR->SetCCATarget ( reinterpret_cast<uint8_t*> ( pset_cca_target ) );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetCCATarget::GetObj ()
{
  return std::make_shared<NetCmdSetCCATarget> (  );
}

