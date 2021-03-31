/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetDutyCycleValue.cpp
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

#include "NetCmdGetDutyCycleValue.h"

NetCmdGetDutyCycleValue::NetCmdGetDutyCycleValue ( )
{
}

NetCmdGetDutyCycleValue::~NetCmdGetDutyCycleValue()
{
}

int NetCmdGetDutyCycleValue::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_dc_value_t get_dc_value;
  #if defined(__arm__)
  GET_ENGPTR->GetDutycycleValue ( reinterpret_cast<void*> ( &get_dc_value ) );
  #endif
  return HandleRsp ( cmd, rsp, MCP_RET_GET_DCVALUE, reinterpret_cast<char*> ( &get_dc_value ), sizeof ( get_dc_value ) );
}

std::shared_ptr<NetCmd> NetCmdGetDutyCycleValue::GetObj ()
{
  return std::make_shared<NetCmdGetDutyCycleValue> (  );
}

