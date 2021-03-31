/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetUniformityCorrectionEnable.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/10/2017 10:40:18 AM
 *  Last Modified:  08/10/2017 10:40:18 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */


#include <string>

#include "NetCmdSetUniformityCorrectionEnable.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdSetUniformityCorrectionEnable::NetCmdSetUniformityCorrectionEnable ( )
{
}

NetCmdSetUniformityCorrectionEnable::~NetCmdSetUniformityCorrectionEnable()
{
}

int NetCmdSetUniformityCorrectionEnable::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_ucenable_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_ucenable_t* pset_ucenable = reinterpret_cast<set_ucenable_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  PRINT_LOG ( LOG_LEVEL_NORMAL, "UC Enable %d", pset_ucenable->enable );
  Warping787::UCSetEnable ( pset_ucenable->enable );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetUniformityCorrectionEnable::GetObj ()
{
  return std::make_shared<NetCmdSetUniformityCorrectionEnable> (  );
}

