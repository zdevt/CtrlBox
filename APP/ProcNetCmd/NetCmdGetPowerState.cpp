/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetPowerState.cpp
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
#include <vector>

#include "NetCmdGetPowerState.h"
#include "PowerSupplyInterface.h"
#include "PowerSupplyDefault.h"

NetCmdGetPowerState::NetCmdGetPowerState ( )
{
}

NetCmdGetPowerState::~NetCmdGetPowerState()
{
}

int NetCmdGetPowerState::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  const int powerNum = 2;
  std::vector<char> vechar;
  vechar.resize ( sizeof ( uint32_t ) + powerNum * sizeof ( MCP_POWER_t ), 0 );
  get_powerstate_t* pget_powerstate = reinterpret_cast<get_powerstate_t*> ( &vechar[0] );
  pget_powerstate->uiPowerNum = powerNum;

  #if defined(__arm__)
  power_status_all_t power_status_all;

  AT91SetGpioOutput ( POWERSUPPLYDEFAULT_GPIO, 0 );
  usleep ( 50 * 1000 );

  PowerSupplyInterface::GetPowerSupplyPtr()->GetAll ( power_status_all );
  strncpy ( ( char* ) ( pget_powerstate->powerState[0].name ), "PowerA", MCP_NAME_LEN );
  pget_powerstate->powerState[0].voltage = power_status_all.voltage;
  pget_powerstate->powerState[0].celsius = power_status_all.celsius;
  pget_powerstate->powerState[0].ampere = power_status_all.ampere;
  pget_powerstate->powerState[0].watt = power_status_all.watt;

  AT91SetGpioOutput ( POWERSUPPLYDEFAULT_GPIO, 1 );
  usleep ( 50 * 1000 );

  PowerSupplyInterface::GetPowerSupplyPtr()->GetAll ( power_status_all );
  strncpy ( ( char* ) ( pget_powerstate->powerState[1].name ), "PowerB", MCP_NAME_LEN );
  pget_powerstate->powerState[1].voltage = power_status_all.voltage;
  pget_powerstate->powerState[1].celsius = power_status_all.celsius;
  pget_powerstate->powerState[1].ampere = power_status_all.ampere;
  pget_powerstate->powerState[1].watt = power_status_all.watt;
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_POWERSTATE, reinterpret_cast<char*> ( &vechar[0] ), vechar.size() );
}

std::shared_ptr<NetCmd> NetCmdGetPowerState::GetObj ()
{
  return std::make_shared<NetCmdGetPowerState> (  );
}

