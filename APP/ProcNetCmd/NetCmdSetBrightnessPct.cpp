/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetBrightnessPct.cpp
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

#include "NetCmdSetBrightnessPct.h"
#include "NetCmdSetDac.h"

NetCmdSetBrightnessPct::NetCmdSetBrightnessPct (  )
{
}

NetCmdSetBrightnessPct::~NetCmdSetBrightnessPct()
{
}

int NetCmdSetBrightnessPct::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_brightnesspct_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_brightnesspct_t* pset_brightnesspct = reinterpret_cast<set_brightnesspct_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  uint16_t maxRgbDac[3];
  GET_ENGPTR->GetMaxDac ( ( void* ) &maxRgbDac[0] );
  uint16_t r, g, b;

  r = ( uint16_t ) ( maxRgbDac[0] * 1.0 * pset_brightnesspct->coef / 100.0 );
  g = ( uint16_t ) ( maxRgbDac[1] * 1.0 * pset_brightnesspct->coef / 100.0 );
  b = ( uint16_t ) ( maxRgbDac[2] * 1.0 * pset_brightnesspct->coef / 100.0 );

  component_dac_value_t dacR, dacG, dacB;
  memset ( reinterpret_cast<void*> ( &dacR ), 0, sizeof ( dacR ) );
  memset ( reinterpret_cast<void*> ( &dacG ), 0, sizeof ( dacG ) );
  memset ( reinterpret_cast<void*> ( &dacB ), 0, sizeof ( dacB ) );

  dacR.red = r;
  dacG.green = g;
  dacB.blue = b;

  GET_ENGPTR->SetLedDacRed ( reinterpret_cast<void*> ( & ( dacR ) ) );
  usleep ( 15 * 1000 );
  GET_ENGPTR->SetLedDacGreen ( reinterpret_cast<void*> ( & ( dacG ) ) );
  usleep ( 15 * 1000 );
  GET_ENGPTR->SetLedDacBlue ( reinterpret_cast<void*> ( & ( dacB ) ) );

  int iBrightnessPct = pset_brightnesspct->coef;
  XmlConfig::SetParam ( "OpticEngine", "BrightnessPct", iBrightnessPct );
  #endif

  HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdSetBrightnessPct::GetObj (  )
{
  return std::make_shared<NetCmdSetBrightnessPct> ();
}

