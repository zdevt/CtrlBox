/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetUsePeriod.cpp
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

#include "NetCmdGetUsePeriod.h"
#include "XmlConfig.h"
#include "OpticEngineInterface.h"

NetCmdGetUsePeriod::NetCmdGetUsePeriod ( )
{
}

NetCmdGetUsePeriod::~NetCmdGetUsePeriod()
{
}

int NetCmdGetUsePeriod::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < sizeof ( MCP_HEADER_t ) )
    return 0;

  get_useperiod_t get_useperiod;
  #if !defined(__i386__) && !defined(__x86_64__)
  GET_ENGPTR->GetUsePeriodRemain ( get_useperiod.useperiodInSec );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_USEPERIOD, reinterpret_cast<char*> ( &get_useperiod ), sizeof ( get_useperiod ) );
}

std::shared_ptr<NetCmd> NetCmdGetUsePeriod::GetObj ()
{
  return std::make_shared<NetCmdGetUsePeriod> (  );
}

