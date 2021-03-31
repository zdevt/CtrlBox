/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetBrightnessPct.cpp
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

#include "NetCmdGetBrightnessPct.h"

NetCmdGetBrightnessPct::NetCmdGetBrightnessPct (  )
{
}

NetCmdGetBrightnessPct::~NetCmdGetBrightnessPct()
{
}

int NetCmdGetBrightnessPct::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_brightnesspct_t get_brightnesspct;
  #if !defined(__i386__) && !defined(__x86_64__)
  int iBrightnessPct = 0;
  XmlConfig::GetParam ( "OpticEngine", "BrightnessPct", iBrightnessPct, 100 );
  get_brightnesspct.coef = ( uint8_t ) iBrightnessPct;
  #endif

  HandleRsp ( cmd, rsp, MCP_RET_GET_BRIGHTNESSPCT, reinterpret_cast<char*> ( &get_brightnesspct ), sizeof ( get_brightnesspct ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdGetBrightnessPct::GetObj (  )
{
  return std::make_shared<NetCmdGetBrightnessPct> ();
}

