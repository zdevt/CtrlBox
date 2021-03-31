/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetTargetLuminance.cpp
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

#include "NetCmdSetTargetLuminance.h"
#include "NetCmdSetDac.h"

NetCmdSetTargetLuminance::NetCmdSetTargetLuminance ( )
{
}

NetCmdSetTargetLuminance::~NetCmdSetTargetLuminance()
{
}

int NetCmdSetTargetLuminance::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_targetluminance_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if !defined(__i386__) && !defined(__x86_64__)
  set_targetluminance_t* pset_targetluminance =
    reinterpret_cast<set_targetluminance_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  const uint32_t maxDac = GET_ENGPTR->GetMaxDac ( NULL );
  uint32_t l = 0;
  component_dac_value_t dac;

  if ( pset_targetluminance->cmd.r == 1 )
  {
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_R_l", l, ( uint32_t ) 0 );
    dac.red = ( uint16_t ) ( ( ( pset_targetluminance->r.r ) * ( 1.0 ) / ( l ) ) * maxDac );
    dac.green = 0;
    dac.blue = 0;

    GET_ENGPTR->SetLedDacRed ( reinterpret_cast<void*> ( & ( dac ) ) );
  }

  if ( pset_targetluminance->cmd.g == 1 )
  {
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_G_l", l, ( uint32_t ) 0 );
    dac.red = 0;
    dac.green = ( uint16_t ) ( ( ( pset_targetluminance->g.g ) * ( 1.0 ) / ( l ) ) * maxDac );
    dac.blue = 0;

    GET_ENGPTR->SetLedDacGreen ( reinterpret_cast<void*> ( & ( dac ) ) );
  }

  if ( pset_targetluminance->cmd.b == 1 )
  {
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_B_l", l, ( uint32_t ) 0 );
    dac.red = 0;
    dac.green = 0;
    dac.blue = ( uint16_t ) ( ( ( pset_targetluminance->b.b ) * ( 1.0 ) / ( l ) ) * maxDac );

    GET_ENGPTR->SetLedDacBlue ( reinterpret_cast<void*> ( & ( dac ) ) );
  }

  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetTargetLuminance::GetObj ()
{
  return std::make_shared<NetCmdSetTargetLuminance> (  );
}

