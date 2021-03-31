/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetHSGValue.cpp
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

#include "NetCmdSetHSGValue.h"
#include "OpticEngineInterface.h"

NetCmdSetHSGValue::NetCmdSetHSGValue ( )
{
}

NetCmdSetHSGValue::~NetCmdSetHSGValue()
{
}

int NetCmdSetHSGValue::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_hsg_value_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_hsg_value_t* pset_hsg_value = reinterpret_cast<set_hsg_value_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  GET_ENGPTR->SetHsgAdjustment ( reinterpret_cast<uint8_t*> ( & ( pset_hsg_value->value ) ) );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetHSGValue::GetObj ()
{
  return std::make_shared<NetCmdSetHSGValue> (  );
}

