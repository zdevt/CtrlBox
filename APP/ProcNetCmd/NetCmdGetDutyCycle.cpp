/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetDutyCycle.cpp
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

#include "NetCmdGetDutyCycle.h"

NetCmdGetDutyCycle::NetCmdGetDutyCycle ( )
{
}

NetCmdGetDutyCycle::~NetCmdGetDutyCycle()
{
}

int NetCmdGetDutyCycle::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_dc_index_t get_dc_index;
  #if defined(__arm__)
  GET_ENGPTR->GetDutycycle ( & ( get_dc_index.dcIndex ) );
  #endif
  return HandleRsp ( cmd, rsp, MCP_RET_GET_DCINDEX, reinterpret_cast<char*> ( &get_dc_index ), sizeof ( get_dc_index ) );
}

std::shared_ptr<NetCmd> NetCmdGetDutyCycle::GetObj ()
{
  return std::make_shared<NetCmdGetDutyCycle> (  );
}

