/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetDspEffect.cpp
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

#include "NetCmdGetDspEffect.h"
#include "XmlConfig.h"

NetCmdGetDspEffect::NetCmdGetDspEffect ( )
{
}

NetCmdGetDspEffect::~NetCmdGetDspEffect()
{
}

int NetCmdGetDspEffect::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < sizeof ( MCP_HEADER_t ) )
    return 0;

  get_dspeffect_t get_dspeffect;

  #if !defined(__i386__) && !defined(__x86_64__)
  int temp = 0;
  XmlConfig::GetParam ( "DeskTopConf", "DspEffect", temp, 0 );
  get_dspeffect.dspEffect = temp;
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_DSPEFFECT, reinterpret_cast<char*> ( &get_dspeffect ), sizeof ( get_dspeffect ) );
}

std::shared_ptr<NetCmd> NetCmdGetDspEffect::GetObj ()
{
  return std::make_shared<NetCmdGetDspEffect> (  );
}

