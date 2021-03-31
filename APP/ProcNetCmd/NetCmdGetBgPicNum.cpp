/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetBgPicNum.cpp
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

#include "NetCmdGetBgPicNum.h"
#include "FpgaImageUserDefPic.h"

NetCmdGetBgPicNum::NetCmdGetBgPicNum (  )
{
}

NetCmdGetBgPicNum::~NetCmdGetBgPicNum()
{
}

int NetCmdGetBgPicNum::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  std::vector<uint32_t> vecuintbgpNum;
  vecuintbgpNum.resize ( 1, 0 );
  #if defined(__arm__)
  FpgaImageUserDefPic::GetBgpNum ( vecuintbgpNum );
  #endif

  HandleRsp ( cmd, rsp, MCP_RET_GET_BGPICNUM, reinterpret_cast<char*> ( &vecuintbgpNum[0] ), vecuintbgpNum.size() * 4 );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdGetBgPicNum::GetObj (  )
{
  return std::make_shared<NetCmdGetBgPicNum> ( );
}

