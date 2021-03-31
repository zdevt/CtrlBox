/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDmdGamma.cpp
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

#include "NetCmdSetDmdGamma.h"
#include "XmlConfig.h"

NetCmdSetDmdGamma::NetCmdSetDmdGamma ( )
{
}

NetCmdSetDmdGamma::~NetCmdSetDmdGamma()
{
}

int NetCmdSetDmdGamma::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_dmd_gamma_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;
  #if !defined(__i386__) && !defined(__x86_64__)
  set_dmd_gamma_t* pset_dmd_gamma = reinterpret_cast<set_dmd_gamma_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  GET_ENGPTR->SetDmdGamma ( pset_dmd_gamma->gammaType );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetDmdGamma::GetObj ()
{
  return std::make_shared<NetCmdSetDmdGamma> (  );
}

