/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetProjType.cpp
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

#include "NetCmdGetProjType.h"
#include "XmlConfig.h"
#include "OpticEngineInterface.h"

NetCmdGetProjType::NetCmdGetProjType ( )
{
}

NetCmdGetProjType::~NetCmdGetProjType()
{
}

int NetCmdGetProjType::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < sizeof ( MCP_HEADER_t ) )
    return 0;

  get_projtype_t get_projtype;
  #if !defined(__i386__) && !defined(__x86_64__)
  GET_ENGPTR->GetProjMode ( get_projtype.type );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_PORJTYPE, reinterpret_cast<char*> ( &get_projtype ), sizeof ( get_projtype ) );
}

std::shared_ptr<NetCmd> NetCmdGetProjType::GetObj ()
{
  return std::make_shared<NetCmdGetProjType> (  );
}

