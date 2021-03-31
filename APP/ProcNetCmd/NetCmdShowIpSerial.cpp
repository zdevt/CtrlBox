/*
 * =====================================================================================
 *
 *       Filename:  NetCmdShowIpSerial.cpp
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

#include "NetCmdShowIpSerial.h"
#include "ShowIpBmp.h"
#include "LogPrint.h"

NetCmdShowIpSerial::NetCmdShowIpSerial (  )
{
}

NetCmdShowIpSerial::~NetCmdShowIpSerial()
{
}

int NetCmdShowIpSerial::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( show_ip_serial_t ) ) )
    return 0;

  #if defined(__arm__)
  show_ip_serial_t* pshow_ip = reinterpret_cast<show_ip_serial_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  if ( 0 == pshow_ip->flag )
    ShowIpBmp::Off();
  else
    ShowIpBmp::On();

  #endif

  //不回应答包
  PRINT_LOG ( LOG_LEVEL_NORMAL, "show ip serial, no response\n" );

  return 0;
}

std::shared_ptr<NetCmd> NetCmdShowIpSerial::GetObj (  )
{
  return std::make_shared<NetCmdShowIpSerial> ();
}

