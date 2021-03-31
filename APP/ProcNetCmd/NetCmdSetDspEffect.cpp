/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDspEffect.cpp
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

#include "NetCmdSetDspEffect.h"
#include "XmlConfig.h"

NetCmdSetDspEffect::NetCmdSetDspEffect ( )
{
}

NetCmdSetDspEffect::~NetCmdSetDspEffect()
{
}

int NetCmdSetDspEffect::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_dspeffect_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if !defined(__i386__) && !defined(__x86_64__)
  //TODO:
  set_dspeffect_t* pset_dspeffect = reinterpret_cast<set_dspeffect_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  GET_ENGPTR->SetDspEffect ( pset_dspeffect->dspEffect );
  XmlConfig::SetParam ( "DeskTopConf", "DspEffect", ( int ) pset_dspeffect->dspEffect );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetDspEffect::GetObj ()
{
  return std::make_shared<NetCmdSetDspEffect> (  );
}

