/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetDmdGamma.cpp
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

#include "NetCmdGetDmdGamma.h"
#include "XmlConfig.h"

NetCmdGetDmdGamma::NetCmdGetDmdGamma ( )
{
}

NetCmdGetDmdGamma::~NetCmdGetDmdGamma()
{
}

int NetCmdGetDmdGamma::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < sizeof ( MCP_HEADER_t ) )
    return 0;

  get_dmd_gamma_t get_dmd_gamma;
  #if !defined(__i386__) && !defined(__x86_64__)
  GET_ENGPTR-> GetDmdGamma ( get_dmd_gamma.gammaType );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_DMDGAMMA, reinterpret_cast<char*> ( &get_dmd_gamma ), sizeof ( get_dmd_gamma ) );
}

std::shared_ptr<NetCmd> NetCmdGetDmdGamma::GetObj ()
{
  return std::make_shared<NetCmdGetDmdGamma> (  );
}

