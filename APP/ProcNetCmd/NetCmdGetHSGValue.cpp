/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetHSGValue.cpp
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

#include "NetCmdGetHSGValue.h"
#include "OpticEngineInterface.h"

NetCmdGetHSGValue::NetCmdGetHSGValue ( )
{
}

NetCmdGetHSGValue::~NetCmdGetHSGValue()
{
}

int NetCmdGetHSGValue::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_hsg_value_t get_hsg_value;
  #if defined(__arm__)
  GET_ENGPTR->GetHsgAdjustment ( reinterpret_cast<uint8_t*> ( & ( get_hsg_value.value ) ) );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_HSGVALUE, reinterpret_cast<char*> ( &get_hsg_value ), sizeof ( get_hsg_value ) );
}

std::shared_ptr<NetCmd> NetCmdGetHSGValue::GetObj ()
{
  return std::make_shared<NetCmdGetHSGValue> (  );
}

