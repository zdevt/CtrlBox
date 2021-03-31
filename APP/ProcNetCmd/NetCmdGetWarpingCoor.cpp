/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetWarpingCoor.cpp
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

#include "NetCmdGetWarpingCoor.h"
#include "XmlConfig.h"
#include "LogPrint.h"
#include "NetCmdSetWarpingCoor.h"
#include "Warping787.h"

NetCmdGetWarpingCoor::NetCmdGetWarpingCoor ( )
{
}

NetCmdGetWarpingCoor::~NetCmdGetWarpingCoor()
{
}

int NetCmdGetWarpingCoor::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() != ( sizeof ( MCP_HEADER_t ) ) )
  {
    PRINT_LOG ( LOG_LEVEL_ERROR, "Illegal cmd package length(%d), expected %d bytes!\n",
                cmd.size(), ( sizeof ( MCP_HEADER_t ) ) );
    return 0;
  }

  MCP_WARPINGCOOR_T mCP_WARPINGCOOR;
  #if !defined(__i386__) && !defined(__x86_64__)

  Warping787::GetWarpingCoor ( reinterpret_cast<void*> ( &mCP_WARPINGCOOR ) );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_WARPINGCOOR, reinterpret_cast<char*> ( &mCP_WARPINGCOOR ), sizeof ( mCP_WARPINGCOOR ) );
}

std::shared_ptr<NetCmd> NetCmdGetWarpingCoor::GetObj ()
{
  return std::make_shared<NetCmdGetWarpingCoor> (  );
}

