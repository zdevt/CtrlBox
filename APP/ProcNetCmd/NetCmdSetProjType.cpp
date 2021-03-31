/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetProjType.cpp
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

#include "NetCmdSetProjType.h"
#include "XmlConfig.h"
#include "OpticEngineInterface.h"

NetCmdSetProjType::NetCmdSetProjType ( )
{
}

NetCmdSetProjType::~NetCmdSetProjType()
{
}

int NetCmdSetProjType::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_projtype_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;
  #if !defined(__i386__) && !defined(__x86_64__)
  set_projtype_t* pset_projtype = reinterpret_cast<set_projtype_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  GET_ENGPTR->SetProjMode ( pset_projtype->type );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetProjType::GetObj ()
{
  return std::make_shared<NetCmdSetProjType> (  );
}

