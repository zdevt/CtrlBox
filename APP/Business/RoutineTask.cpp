/*
 * =====================================================================================
 *
 *       Filename:  RoutineTask.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月09日 22时40分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include "RoutineTask.h"
#include "OpticEngineInterface.h"
#include "FpgaDev.h"
#include "FpgaReg.h"
#include "LogPrint.h"
#include "PowerOn.h"

all_device_status_t RoutineTask::m_all_device_status;

RoutineTask::RoutineTask()
{

}

RoutineTask::~RoutineTask()
{

}

int RoutineTask::ReadMainboardFan( )
{
  m_all_device_status.mainboard_fan.a = FpgaGetReg ( FPGA_FAN1_RATE );
  m_all_device_status.mainboard_fan.b = FpgaGetReg ( FPGA_FAN2_RATE );

  #if 0
  PRINT_LOG ( LOG_LEVEL_NORMAL, "Fan a=%d b=%d\n",
              m_all_device_status.mainboard_fan.a,
              m_all_device_status.mainboard_fan.b );
  #endif

  return 0;
}

int RoutineTask::ReadDmdTemp( )
{
  GET_ENGPTR->GetDmdTemp ( m_all_device_status.dmdTemp );

  PRINT_LOG ( LOG_LEVEL_NORMAL, "DmdTemp=%d\n", m_all_device_status.dmdTemp );
  return 0;
}

int RoutineTask::ReadLedTemp( )
{
  GET_ENGPTR->GetLedTemp ( reinterpret_cast<int*> ( & ( m_all_device_status.led_rgb_temp ) ) );

  PRINT_LOG ( LOG_LEVEL_NORMAL, "LedTemp r=%d g=%d b=%d\n",
              m_all_device_status.led_rgb_temp.r,
              m_all_device_status.led_rgb_temp.g,
              m_all_device_status.led_rgb_temp.b );
  return 0;
}

int RoutineTask::ReadLedStatus ( )
{
  ddp442x_led_status_t ddp442x_led_status;
  GET_ENGPTR->GetLedStatus (
    reinterpret_cast<void*> ( & ( ddp442x_led_status ) ) );

  m_all_device_status.led_status.dT = ddp442x_led_status.dT;

  m_all_device_status.led_status.rV = ddp442x_led_status.rV;
  m_all_device_status.led_status.rC = ddp442x_led_status.rC;

  m_all_device_status.led_status.gV = ddp442x_led_status.gV;
  m_all_device_status.led_status.gC = ddp442x_led_status.gC;

  m_all_device_status.led_status.bV = ddp442x_led_status.bV;
  m_all_device_status.led_status.bC = ddp442x_led_status.bC;

  PRINT_LOG ( LOG_LEVEL_NORMAL, "dT=%d rV=%d rC=%d gV=%d gC=%d bV=%d bC=%d\n",
              ddp442x_led_status.dT,
              ddp442x_led_status.rC, ddp442x_led_status.rV,
              ddp442x_led_status.gC, ddp442x_led_status.gV,
              ddp442x_led_status.bC, ddp442x_led_status.bV );

  return 0;
}

int RoutineTask::ReadPowerStatus ( )
{
  return 0;
}

int RoutineTask::ReadAll()
{
  #if 0

  if ( PowerOn::GetOnOffFlag() )
  {
    ReadMainboardFan( );
    ReadDmdTemp( );
    ReadLedTemp( );
    ReadLedStatus ( ); /*  led driver wtemp voltage current ..*/
    ReadPowerStatus ( );
  }

  #endif

  return 0;
}

