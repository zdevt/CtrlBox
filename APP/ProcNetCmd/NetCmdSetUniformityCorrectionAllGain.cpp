/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetUniformityCorrectionAllGain.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/10/2017 11:35:31 AM
 *  Last Modified:  08/10/2017 11:35:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */


#include <string>

#include "NetCmdSetUniformityCorrectionAllGain.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdSetUniformityCorrectionAllGain::NetCmdSetUniformityCorrectionAllGain ( )
{
}

NetCmdSetUniformityCorrectionAllGain::~NetCmdSetUniformityCorrectionAllGain()
{
}

int NetCmdSetUniformityCorrectionAllGain::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_ucallgain_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_ucallgain_t* pset_ucallgain = reinterpret_cast<set_ucallgain_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  Warping787::UCSetAllGain ( pset_ucallgain->level, pset_ucallgain->gainNum, pset_ucallgain->gain );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetUniformityCorrectionAllGain::GetObj ()
{
  return std::make_shared<NetCmdSetUniformityCorrectionAllGain> (  );
}

