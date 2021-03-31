/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetEngineType.cpp
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

#include "NetCmdGetEngineType.h"
#include "OpticEngineThin.h"

NetCmdGetEngineType::NetCmdGetEngineType (  )
{
}

NetCmdGetEngineType::~NetCmdGetEngineType()
{
}

int NetCmdGetEngineType::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_engine_type_t get_engine_type;
  #if defined(__arm__)
  std::string engineType;
  std::string defaultEngineType = OPTIC_ENGINE_THIN_NAME;
  XmlConfig::GetParam ( "OpticEngine", "EngineType", engineType, defaultEngineType );
  strncpy ( reinterpret_cast<char*> ( get_engine_type.type ), engineType.c_str(), 24 );
  PRINT_LOG ( LOG_LEVEL_NORMAL, "%s\n", engineType.c_str() );
  #endif

  HandleRsp ( cmd, rsp, MCP_RET_GET_ENGINETYPE, reinterpret_cast<char*> ( &get_engine_type ), sizeof ( get_engine_type ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdGetEngineType::GetObj (  )
{
  return std::make_shared<NetCmdGetEngineType> ( );
}

