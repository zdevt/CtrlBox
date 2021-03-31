/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetUniformityCorrectionAllGain.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/10/2017 02:05:20 PM
 *  Last Modified:  08/10/2017 02:05:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */


#include <string>

#include "NetCmdGetUniformityCorrectionAllGain.h"
#include "XmlConfig.h"
#include "Warping787.h"

NetCmdGetUniformityCorrectionAllGain::NetCmdGetUniformityCorrectionAllGain ( )
{
}

NetCmdGetUniformityCorrectionAllGain::~NetCmdGetUniformityCorrectionAllGain()
{
}

int NetCmdGetUniformityCorrectionAllGain::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( get_ucallgain_t ) ) )
    return 0;

  get_ucallgain_t* pget_ucallgain =
    reinterpret_cast<get_ucallgain_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  std::vector<uint16_t> vecData ( pget_ucallgain->gainNum, 0 );
  #if defined(__arm__)
  Warping787::UCGetAllGain ( pget_ucallgain->level, pget_ucallgain->gainNum, &vecData[0] );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_UCALLGAIN, reinterpret_cast<char*> ( &vecData[0] ), vecData.size() * 2 );
}

std::shared_ptr<NetCmd> NetCmdGetUniformityCorrectionAllGain::GetObj ()
{
  return std::make_shared<NetCmdGetUniformityCorrectionAllGain> (  );
}

