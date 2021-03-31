/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetUsePeriodEnableEnable.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07/31/2017 10:13:31 AM
 *  Last Modified:  07/31/2017 10:13:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */


#include <string>

#include "NetCmdGetUsePeriodEnable.h"
#include "XmlConfig.h"
#include "OpticEngineInterface.h"

NetCmdGetUsePeriodEnable::NetCmdGetUsePeriodEnable ( )
{
}

NetCmdGetUsePeriodEnable::~NetCmdGetUsePeriodEnable()
{
}

int NetCmdGetUsePeriodEnable::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < sizeof ( MCP_HEADER_t ) )
    return 0;

  get_useperiod_enable_t get_useperiod_enable;
  #if !defined(__i386__) && !defined(__x86_64__)
  get_useperiod_enable.enable = ( uint8_t ) GET_ENGPTR->GetUsePeriodEnable ( );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_USEPERIODENABLE, reinterpret_cast<char*> ( &get_useperiod_enable ), sizeof ( get_useperiod_enable ) );
}

std::shared_ptr<NetCmd> NetCmdGetUsePeriodEnable::GetObj ()
{
  return std::make_shared<NetCmdGetUsePeriodEnable> (  );
}

