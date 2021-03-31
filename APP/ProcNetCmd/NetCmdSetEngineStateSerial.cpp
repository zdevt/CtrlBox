/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetEngineStateSerial.cpp
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

#include "NetCmdSetEngineStateSerial.h"
#include "PowerOn.h"

NetCmdSetEngineStateSerial::NetCmdSetEngineStateSerial (  )
{
}

NetCmdSetEngineStateSerial::~NetCmdSetEngineStateSerial()
{
}

int NetCmdSetEngineStateSerial::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_engine_state_serial_t ) ) )
    return 0;

  #if defined(__arm__)
  set_engine_state_serial_t* pset_engine_state = reinterpret_cast<set_engine_state_serial_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  PowerOn::SetOnOrOff ( pset_engine_state->state );
  #endif

  return 0;
}

std::shared_ptr<NetCmd> NetCmdSetEngineStateSerial::GetObj (  )
{
  return std::make_shared<NetCmdSetEngineStateSerial> ();
}

