/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetCCAEnable.cpp
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

#include "NetCmdGetCCAEnable.h"
#include "OpticEngineInterface.h"
#include "DmdDdp442xReg.h"

NetCmdGetCCAEnable::NetCmdGetCCAEnable ( )
{
}

NetCmdGetCCAEnable::~NetCmdGetCCAEnable()
{
}

int NetCmdGetCCAEnable::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  uint8_t enable;
  ddp442x_alg_enable_t ddp442x_alg_enable;
  #if defined(__arm__)
  GET_ENGPTR->GetAlgorithmEnable ( ddp442x_alg_enable.data );
  enable = ddp442x_alg_enable.cca;
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_CCAENABLE, reinterpret_cast<char*> ( &enable ), sizeof ( enable ) );
}

std::shared_ptr<NetCmd> NetCmdGetCCAEnable::GetObj ()
{
  return std::make_shared<NetCmdGetCCAEnable> (  );
}

