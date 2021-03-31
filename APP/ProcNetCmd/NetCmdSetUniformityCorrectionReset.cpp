/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetUniformityCorrectionReset.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/10/2017 11:04:53 AM
 *  Last Modified:  08/10/2017 11:04:53 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */


#include <string>

#include "NetCmdSetUniformityCorrectionReset.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdSetUniformityCorrectionReset::NetCmdSetUniformityCorrectionReset ( )
{
}

NetCmdSetUniformityCorrectionReset::~NetCmdSetUniformityCorrectionReset()
{
}

int NetCmdSetUniformityCorrectionReset::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  Warping787::UCResetGain ( );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetUniformityCorrectionReset::GetObj ()
{
  return std::make_shared<NetCmdSetUniformityCorrectionReset> (  );
}

