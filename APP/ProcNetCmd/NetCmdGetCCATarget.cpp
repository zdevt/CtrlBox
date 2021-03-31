/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetCCATarget.cpp
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

#include "NetCmdGetCCATarget.h"
#include "OpticEngineInterface.h"

NetCmdGetCCATarget::NetCmdGetCCATarget ( )
{
}

NetCmdGetCCATarget::~NetCmdGetCCATarget()
{
}

int NetCmdGetCCATarget::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( get_cca_target_index_t ) ) )
    return 0;

  get_cca_target_t get_cca_target;

  #if defined(__arm__)
  get_cca_target_index_t* pget_cca_target_index = reinterpret_cast<get_cca_target_index_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  get_cca_target.colorIndex = pget_cca_target_index->colorIndex;
  GET_ENGPTR->GetCCATarget ( reinterpret_cast<uint8_t*> ( & ( get_cca_target ) ) );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_CCATARGET, reinterpret_cast<char*> ( &get_cca_target ), sizeof ( get_cca_target ) );
}

std::shared_ptr<NetCmd> NetCmdGetCCATarget::GetObj ()
{
  return std::make_shared<NetCmdGetCCATarget> (  );
}

