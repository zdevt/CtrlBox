/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetTargetLuminance.cpp
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

#include "NetCmdGetTargetLuminance.h"

NetCmdGetTargetLuminance::NetCmdGetTargetLuminance ( )
{
}

NetCmdGetTargetLuminance::~NetCmdGetTargetLuminance()
{
}

int NetCmdGetTargetLuminance::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( get_targetluminance_cmd_t ) ) )
    return 0;

  get_targetluminance_cmd_t* pget_targetluminance_cmd =
    reinterpret_cast<get_targetluminance_cmd_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  get_targetluminance_t get_targetluminance;
  pget_targetluminance_cmd->mask = 0;

  #if !defined(__i386__) && !defined(__x86_64__)

  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_TARGETLUMINANCE, reinterpret_cast<char*> ( &get_targetluminance ), sizeof ( get_targetluminance ) );
}

std::shared_ptr<NetCmd> NetCmdGetTargetLuminance::GetObj ()
{
  return std::make_shared<NetCmdGetTargetLuminance> (  );
}

