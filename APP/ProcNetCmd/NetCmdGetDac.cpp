/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetDac.cpp
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

#include "NetCmdGetDac.h"
#include "OpticEngineInterface.h"

NetCmdGetDac::NetCmdGetDac ( )
{
}

NetCmdGetDac::~NetCmdGetDac()
{
}

int NetCmdGetDac::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( get_dac_cmd_t ) ) )
    return 0;

  get_dac_t get_dac;
  #if defined(__arm__)
  get_dac_cmd_t* pget_dac_cmd = reinterpret_cast<get_dac_cmd_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  get_dac_mask_t* pget_dac_mask = reinterpret_cast<get_dac_mask_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) + sizeof ( uint16_t ) );

  int ledDacTime = 12;

  if ( pget_dac_cmd->basic == 1 )
  {
    if ( pget_dac_mask->red )
      GET_ENGPTR->GetLedDacRedBasic ( reinterpret_cast<void*> ( & ( get_dac.red ) ) );

    if ( pget_dac_mask->green )
      GET_ENGPTR->GetLedDacGreenBasic ( reinterpret_cast<void*> ( & ( get_dac.green ) ) );

    if ( pget_dac_mask->blue )
      GET_ENGPTR->GetLedDacBlueBasic ( reinterpret_cast<void*> ( & ( get_dac.blue ) ) );
  }
  else
  {
    usleep ( ledDacTime * 1000 );

    if ( pget_dac_mask->red )
      GET_ENGPTR->GetLedDacRed ( reinterpret_cast<void*> ( & ( get_dac.red ) ) );

    usleep ( ledDacTime * 1000 );

    if ( pget_dac_mask->green )
      GET_ENGPTR->GetLedDacGreen ( reinterpret_cast<void*> ( & ( get_dac.green ) ) );

    usleep ( ledDacTime * 1000 );

    if ( pget_dac_mask->blue )
      GET_ENGPTR->GetLedDacBlue ( reinterpret_cast<void*> ( & ( get_dac.blue ) ) );
  }

  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_DAC, reinterpret_cast<char*> ( &get_dac ), sizeof ( get_dac ) );
}

std::shared_ptr<NetCmd> NetCmdGetDac::GetObj ()
{
  return std::make_shared<NetCmdGetDac> (  );
}

