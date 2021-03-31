/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetFanPwmEngine.cpp
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

#include "NetCmdSetFanPwmEngine.h"
#include "XmlConfig.h"

NetCmdSetFanPwmEngine::NetCmdSetFanPwmEngine ( )
{
}

NetCmdSetFanPwmEngine::~NetCmdSetFanPwmEngine()
{
}

int NetCmdSetFanPwmEngine::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_fan_pwm_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if !defined(__i386__) && !defined(__x86_64__)
  set_fan_pwm_t* pset_fan_pwm = reinterpret_cast<set_fan_pwm_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  GET_ENGPTR->SetFanPwm ( pset_fan_pwm->fan_id, pset_fan_pwm->fan_pwm );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetFanPwmEngine::GetObj ()
{
  return std::make_shared<NetCmdSetFanPwmEngine> (  );
}

