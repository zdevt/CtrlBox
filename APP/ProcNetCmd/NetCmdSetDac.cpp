/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDac.cpp
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

#include "NetCmdSetDac.h"
#include "OpticEngineInterface.h"

NetCmdSetDac::NetCmdSetDac ( )
{
}

NetCmdSetDac::~NetCmdSetDac()
{
}

int NetCmdSetDac::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_dac_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_dac_t* pset_dac = reinterpret_cast<set_dac_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );


  if ( pset_dac->basic == 1 )
  {
    if ( pset_dac->mask.red )
      GET_ENGPTR->SetLedDacRedBasic ( reinterpret_cast<void*> ( & ( pset_dac->red ) ) );


    if ( pset_dac->mask.green )
      GET_ENGPTR->SetLedDacGreenBasic ( reinterpret_cast<void*> ( & ( pset_dac->green ) ) );


    if ( pset_dac->mask.blue )
      GET_ENGPTR->SetLedDacBlueBasic ( reinterpret_cast<void*> ( & ( pset_dac->blue ) ) );
  }
  else
  {
    if ( pset_dac->mask.red )
      GET_ENGPTR->SetLedDacRed ( reinterpret_cast<void*> ( & ( pset_dac->red ) ) );


    if ( pset_dac->mask.green )
      GET_ENGPTR->SetLedDacGreen ( reinterpret_cast<void*> ( & ( pset_dac->green ) ) );


    if ( pset_dac->mask.blue )
      GET_ENGPTR->SetLedDacBlue ( reinterpret_cast<void*> ( & ( pset_dac->blue ) ) );
  }

  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetDac::GetObj ()
{
  return std::make_shared<NetCmdSetDac> (  );
}

