/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetEngineType.cpp
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

#include "NetCmdSetEngineType.h"

NetCmdSetEngineType::NetCmdSetEngineType (  )
{
}

NetCmdSetEngineType::~NetCmdSetEngineType()
{
}

int NetCmdSetEngineType::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_engine_type_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_engine_type_t* pset_engine_type = reinterpret_cast<set_engine_type_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  std::string engineType = ( char* ) ( &pset_engine_type->type[0] );
  XmlConfig::SetParam ( "OpticEngine", "EngineType", engineType );
  #endif

  HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdSetEngineType::GetObj (  )
{
  return std::make_shared<NetCmdSetEngineType> ( );
}

