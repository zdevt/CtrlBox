/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetUniformityCorrectionGain.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/10/2017 11:09:22 AM
 *  Last Modified:  08/10/2017 11:09:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */


#include <string>

#include "NetCmdSetUniformityCorrectionGain.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdSetUniformityCorrectionGain::NetCmdSetUniformityCorrectionGain ( )
{
}

NetCmdSetUniformityCorrectionGain::~NetCmdSetUniformityCorrectionGain()
{
}

int NetCmdSetUniformityCorrectionGain::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_ucgain_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_ucgain_t* pset_ucgain = reinterpret_cast<set_ucgain_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  Warping787::UCSetGain ( pset_ucgain->level, pset_ucgain->color, pset_ucgain->x, pset_ucgain->y, pset_ucgain->gain );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetUniformityCorrectionGain::GetObj ()
{
  return std::make_shared<NetCmdSetUniformityCorrectionGain> (  );
}

