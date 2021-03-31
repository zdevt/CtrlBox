/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetLlcState.cpp
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

#include "NetCmdGetLlcState.h"
#include "XmlConfig.h"
#include "LogPrint.h"

NetCmdGetLlcState::NetCmdGetLlcState ( )
{
}

NetCmdGetLlcState::~NetCmdGetLlcState()
{
}

int NetCmdGetLlcState::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() != ( sizeof ( MCP_HEADER_t ) ) )
  {
    PRINT_LOG ( LOG_LEVEL_ERROR, "Illegal cmd package length(%d), expected %d bytes!\n",
                cmd.size(), ( sizeof ( MCP_HEADER_t ) ) );
    return 0;
  }

  get_llc_state_t get_llc_state;
  #if !defined(__i386__) && !defined(__x86_64__)
  int temp = 0;
  XmlConfig::GetParam ( "OpticEngine", "LlcState", temp, 0 );
  get_llc_state.ucType = temp;
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_LLCSTATE, reinterpret_cast<char*> ( &get_llc_state ), sizeof ( get_llc_state ) );
}

std::shared_ptr<NetCmd> NetCmdGetLlcState::GetObj ()
{
  return std::make_shared<NetCmdGetLlcState> (  );
}

