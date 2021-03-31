/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetSerialID.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  09/18/2017 03:55:28 PM
 *  Last Modified:  09/18/2017 03:55:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <string>
#include <arpa/inet.h>

#include "NetCmdGetSerialID.h"
#include "GetNetWork.h"

NetCmdGetSerialID::NetCmdGetSerialID ( )
{
}

NetCmdGetSerialID::~NetCmdGetSerialID()
{
}

int NetCmdGetSerialID::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( get_serialid_t ) ) )
  {
    return 0;
  }

  std::string ip, mask;
  GetNetWork::GetIp ( ip, mask );
  uint16_t sessionid = ( uint16_t ) ( ( ( uint32_t ) inet_addr ( ip.c_str() ) ) >> 16 );

  get_serialid_t* pget_serialid = reinterpret_cast<get_serialid_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  uint16_t* pExceptionID = NULL;

  for ( unsigned int i = 0; i < pget_serialid->exceptionNum; ++i )
  {
    pExceptionID = ( uint16_t* ) ( pget_serialid->exceptionID + i );

    if ( ( *pExceptionID ) == sessionid )
    {
      return 0;
    }
  }

  rsp.clear();
  rsp.resize ( sizeof ( uint16_t ), 0 );
  memcpy ( reinterpret_cast<void*> ( &rsp[0] ), ( void* ) &sessionid, sizeof ( uint16_t ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdGetSerialID::GetObj ()
{
  return std::make_shared<NetCmdGetSerialID> (  );
}

