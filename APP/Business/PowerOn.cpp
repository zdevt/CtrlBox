/*
 * =====================================================================================
 *
 *       Filename:  PowerOn.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/11/2015 11:09:30 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include "PowerOn.h"
#include "ControlBoxInterface.h"
#include "OpticEngineInterface.h"
#include "MainboardInterface.h"
#include "XmlConfig.h"
#include "ShowIpBmp.h"
#include "Locker.h"
#include "FpgaDev.h"
#include "Led74Hc595D.h"

pthread_t PowerOn::m_tid;
pthread_mutex_t PowerOn::m_mutex = PTHREAD_MUTEX_INITIALIZER;
bool PowerOn::flag = false;

PowerOn::PowerOn()
{

}

PowerOn::~PowerOn()
{

}

/*  开机完毕后执行相关事宜 */
void* PowerOn::AfterOnTask ( void* p )
{
  #if 0
  unsigned int temp;

  if ( !XmlConfig::GetParam ( "CubeWallConf", "ID", temp, 0u ) )
  {
    ShowIpBmp::On();
    sleep ( 10 );
    ShowIpBmp::Off();
  }

  /*  check mainboard fan */
  uint32_t speed  = 0;
  GET_MBPTR->GetFanSpeed ( 0, speed );

  if ( speed < 5 )
    Led74Hc595D::Disp ( "F." );

  #endif

  return NULL;
}

bool PowerOn::GetOnOffFlag( )
{
  //flag = FpgaDev::IsLoad();
  return flag;
}

bool PowerOn::On()
{
  #if defined(__arm__)

  /*  如果授权使用非法 禁止开机*/
  if ( !GET_ENGPTR->CheckUsePeriodValid() )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "UsePeriod Time Out!\n" );
    return false;
  }

  if ( ! GetOnOffFlag() )
  {
    if ( !GET_CTBOXPTR->Open() )
      return false;

    Led74Hc595D::Disp ( "5" );

    if ( 0 != GET_ENGPTR->SetPowerState ( CUBE_POWER_ON ) )
      return false;

    Led74Hc595D::Disp ( "x0" );

    AfterOnTask ( NULL );
    usleep ( 10 * 1000 );

    flag = true;
  }
  else
    PRINT_LOG ( LOG_LEVEL_NORMAL, " %s\n", GetOnOffFlag() ? "true" : "false" );

  #endif
  return false;
}

bool PowerOn::Off()
{
  #if defined(__arm__)
  GET_ENGPTR->SetPowerState ( CUBE_POWER_OFF );
  GET_CTBOXPTR->Close();
  Led74Hc595D::Disp ( "." );
  flag = false;
  #endif

  return flag;
}

bool PowerOn::SetOnOrOff ( uint8_t state )
{
  Locker locker ( &m_mutex );
  uint8_t onoff = state;

  bool ret = false;
  int stacksize = 32 * 1024; //32K
  pthread_attr_t attr;

  if ( 0 == pthread_attr_init ( &attr ) &&
       0 == pthread_attr_setstacksize ( &attr, stacksize ) &&
       0 == pthread_create ( &m_tid, &attr, PowerOn::SetOnOrOffTask, reinterpret_cast<void*> ( &onoff ) )
     )
  {
    sleep ( 1 );
    ret = true;
  }

  pthread_attr_destroy ( &attr );

  return ret;
}

bool PowerOn::_SetOnOrOff ( uint8_t state )
{
  if ( CUBE_POWER_ON == state )
    On();
  else
    Off();

  return true;
}

void* PowerOn::SetOnOrOffTask ( void* p )
{
  PTHREAD_DETACH;
  uint8_t* pOnoff = reinterpret_cast<uint8_t*> ( p );
  _SetOnOrOff ( *pOnoff );
  return NULL;
}

void PowerOn::CheckOnOffKey( )
{
  static int count = 0;

  if ( ! GET_MBPTR->GetOnOffGpio() )
    ++count;
  else
    count = 0;

  if ( count >= 3 )
  {
    if ( GetOnOffFlag() )
      Off();
    else
      On();

    count = 0;
  }
}

