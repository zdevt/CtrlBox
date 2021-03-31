/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetLlcState.cpp
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

#include "NetCmdSetLlcState.h"
#include "XmlConfig.h"
#include "FpgaReg.h"
#include "LightBrightnessCompensation.h"

NetCmdSetLlcState::NetCmdSetLlcState ( )
{
}

NetCmdSetLlcState::~NetCmdSetLlcState()
{
}

int NetCmdSetLlcState::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() != ( sizeof ( MCP_HEADER_t ) + sizeof ( set_llc_state_t ) ) )
  {
    PRINT_LOG ( LOG_LEVEL_ERROR, "Illegal cmd package length(%d), expected %d bytes!\n",
                cmd.size(), ( sizeof ( MCP_HEADER_t ) + sizeof ( set_llc_state_t ) ) );
    return 0;
  }

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if !defined(__i386__) && !defined(__x86_64__)
  set_llc_state_t* pset_llc_state = reinterpret_cast<set_llc_state_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  XmlConfig::SetParam ( "OpticEngine", "LlcState", ( int ) pset_llc_state->ucType );

  if ( pset_llc_state->ucType )
    LightBrightnessCompensation::WriteDataToFPGA ( "/app/lbcdata.bin" );
  else
    FPGADisableLBCControl();

  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetLlcState::GetObj ()
{
  return std::make_shared<NetCmdSetLlcState> (  );
}

