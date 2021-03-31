/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetUniformityCorrectionEnable.cpp
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

#include "NetCmdGetUniformityCorrectionEnable.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdGetUniformityCorrectionEnable::NetCmdGetUniformityCorrectionEnable ( )
{
}

NetCmdGetUniformityCorrectionEnable::~NetCmdGetUniformityCorrectionEnable()
{
}

int NetCmdGetUniformityCorrectionEnable::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < sizeof ( MCP_HEADER_t ) )
    return 0;

  get_ucenable_t get_ucenable;

  #if defined(__arm__)
  Warping787::UCGetEnable ( get_ucenable.enable );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_UCENABLE, reinterpret_cast<char*> ( &get_ucenable ), sizeof ( get_ucenable ) );
}

std::shared_ptr<NetCmd> NetCmdGetUniformityCorrectionEnable::GetObj ()
{
  return std::make_shared<NetCmdGetUniformityCorrectionEnable> (  );
}

