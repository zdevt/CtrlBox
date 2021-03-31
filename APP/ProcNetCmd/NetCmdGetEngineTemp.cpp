/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetEngineTemp.cpp
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

#include "NetCmdGetEngineTemp.h"

NetCmdGetEngineTemp::NetCmdGetEngineTemp (  )
{
}

NetCmdGetEngineTemp::~NetCmdGetEngineTemp()
{
}

int NetCmdGetEngineTemp::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_engine_temp_t get_engine_temp;
  get_engine_temp.redTemp   = 28 + ( random() % 2 );
  get_engine_temp.greenTemp = 33 + ( random() % 5 );
  get_engine_temp.blueTemp  = 31 + ( random() % 3 );
  #if !defined(__i386__) && !defined(__x86_64__)
  /*  to do  */
  #endif

  HandleRsp ( cmd, rsp, MCP_RET_GET_ENGINETEMP, reinterpret_cast<char*> ( &get_engine_temp ), sizeof ( get_engine_temp ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdGetEngineTemp::GetObj (  )
{
  return std::make_shared<NetCmdGetEngineTemp> ( );
}

