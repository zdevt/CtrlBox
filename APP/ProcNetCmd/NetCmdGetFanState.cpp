/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetFanState.cpp
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
#include <vector>

#include "NetCmdGetFanState.h"
#include "MainboardInterface.h"
#include "OpticEngineInterface.h"

NetCmdGetFanState::NetCmdGetFanState ( )
{
}

NetCmdGetFanState::~NetCmdGetFanState()
{
}

int NetCmdGetFanState::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( get_fanstate_cmd_t ) ) )
    return 0;

  std::vector<char> vechar;
  vechar.resize ( sizeof ( uint32_t ) + 1 * sizeof ( MCP_FAN_t ), 0 );

  #if !defined(__i386__) && !defined(__x86_64__)
  get_fanstate_cmd_t* pget_fanstate_cmd = reinterpret_cast<get_fanstate_cmd_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  get_fanstate_t* pget_fanstate = NULL;

  if ( pget_fanstate_cmd->uiFanType == 0 ) /*  Engine Fan */
  {
    vechar.resize ( sizeof ( uint32_t ) + 4 * sizeof ( MCP_FAN_t ), 0 );

    pget_fanstate = reinterpret_cast<get_fanstate_t*> ( &vechar[0] );
    pget_fanstate->uiFanNum = 4;
    uint16_t speed;

    memcpy ( ( pget_fanstate->fanstate ) [0].name, "NoUse", strlen ( "NoUse" ) );
    memcpy ( ( pget_fanstate->fanstate ) [3].name, "NoUse", strlen ( "NoUse" ) );

    if ( !GET_ENGPTR->GetFanSpeed ( 1, speed ) )
      ( pget_fanstate->fanstate ) [1].status = 1;

    ( pget_fanstate->fanstate ) [1].rate = speed;
    memcpy ( ( pget_fanstate->fanstate ) [1].name, "LedDriver", strlen ( "LedDriver" ) );

    if ( !GET_ENGPTR->GetFanSpeed ( 2, speed ) )
      ( pget_fanstate->fanstate ) [2].status = 1;

    ( pget_fanstate->fanstate ) [2].rate = speed;
    memcpy ( ( pget_fanstate->fanstate ) [2].name, "Led", strlen ( "Led" ) );
  }
  else if ( pget_fanstate_cmd->uiFanType == 1 ) /*  Mainboard Fan */
  {
    vechar.resize ( sizeof ( uint32_t ) + 2 * sizeof ( MCP_FAN_t ), 0 );

    pget_fanstate = reinterpret_cast<get_fanstate_t*> ( &vechar[0] );
    pget_fanstate->uiFanNum = 2;

    memcpy ( ( pget_fanstate->fanstate ) [0].name, "MBFan1", strlen ( "MBFan1" ) );
    GET_MBPTR->GetFanSpeed ( 0, ( pget_fanstate->fanstate ) [0].rate );

    memcpy ( ( pget_fanstate->fanstate ) [1].name, "MBFan2", strlen ( "MBFan2" ) );
    GET_MBPTR->GetFanSpeed ( 1, ( pget_fanstate->fanstate ) [1].rate );
  }

  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_FANSTATE, reinterpret_cast<char*> ( &vechar[0] ), vechar.size() );
}

std::shared_ptr<NetCmd> NetCmdGetFanState::GetObj ()
{
  return std::make_shared<NetCmdGetFanState> (  );
}

