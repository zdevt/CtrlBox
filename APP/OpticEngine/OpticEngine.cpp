/*
 * =====================================================================================
 *
 *       Filename:  OpticEngine.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/11/2015 10:49:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include "OpticEngine.h"


OpticEngine::OpticEngine ( std::string enginename )
  : m_enginename ( enginename )
{

}

OpticEngine::~OpticEngine()
{

}

std::string OpticEngine::GetEngineName()
{
  return m_enginename;
}

bool OpticEngine::SetWorkTime ( )
{
  static uint16_t cnt = 0;
  uint32_t workTime = 0;
  uint32_t temp = 15 * 60;

  if ( 0 == ( ++cnt % ( temp ) ) )
  {
    GetWorkTime ( workTime );
    workTime += temp;
    SetWorkTime ( workTime );
  }

  return true;
}

bool OpticEngine::SetWorkTime ( uint32_t workTime )
{
  XmlConfig::SetParam ( "OpticEngine", "WorkTime", workTime );
  return true;
}

bool OpticEngine::GetWorkTime ( uint32_t& workTime )
{
  uint32_t temp = 0;
  XmlConfig::GetParam ( "OpticEngine", "WorkTime", workTime, temp );
  return true;
}

bool OpticEngine::SetUsePeriodEnable ( uint8_t enable )
{
  uint32_t workTime = 0;
  uint32_t iEnable = 0;

  if ( enable == 1 )
    iEnable = 1;

  XmlConfig::SetParam ( "OpticEngine", "UsePeriodEnable", iEnable );

  if ( 1 == enable )
  {
    GetWorkTime ( workTime );
    XmlConfig::SetParam ( "OpticEngine", "UsePeriodStartTime", workTime );
  }

  return true;
}

bool::OpticEngine::GetUsePeriodEnable( )
{
  uint32_t itemp = 0;
  uint32_t ienable = 0;
  XmlConfig::GetParam ( "OpticEngine", "UsePeriodEnable", ienable, itemp );

  if ( ienable == 1 )
    return true;

  return false;
}

bool OpticEngine::SetUsePeriod ( uint32_t usePeriodInSec )
{
  uint32_t workTime = 0;
  GetWorkTime ( workTime );
  XmlConfig::SetParam ( "OpticEngine", "UsePeriodStartTime", workTime );
  XmlConfig::SetParam ( "OpticEngine", "UsePeriodTime", usePeriodInSec );
  return true;
}

bool OpticEngine::GetUsePeriod ( uint32_t& usePeriodInSec )
{
  uint32_t temp = 0;
  XmlConfig::GetParam ( "OpticEngine", "UsePeriodTime", usePeriodInSec, temp );
  return true;
}

bool OpticEngine::GetUsePeriodStartTime ( uint32_t& startTime )
{
  uint32_t temp = 0;
  XmlConfig::GetParam ( "OpticEngine", "UsePeriodStartTime", startTime, temp );
  return true;
}

bool OpticEngine::GetUsePeriodRemain ( uint32_t& usePeriodInSecRemain )
{
  uint32_t workTime = 0;
  uint32_t startTime = 0;
  uint32_t usePeriodInSec = 0;

  GetWorkTime ( workTime );
  GetUsePeriodStartTime ( startTime );
  GetUsePeriod ( usePeriodInSec );

  //PRINT_LOG ( LOG_LEVEL_NORMAL, "%d, %d, %d\n", workTime, startTime, usePeriodInSec );

  if ( ( workTime - startTime ) >= usePeriodInSec )
    usePeriodInSecRemain = 0;
  else
    usePeriodInSecRemain = usePeriodInSec - ( workTime - startTime );

  return true;
}

bool OpticEngine::CheckUsePeriodValid( )
{
  if ( !GetUsePeriodEnable() )
    return true;

  uint32_t usePeriodInSecRemain = 0;
  GetUsePeriodRemain ( usePeriodInSecRemain );

  //PRINT_LOG ( LOG_LEVEL_NORMAL, "usePeriodInSecRemain =%d\n", usePeriodInSecRemain );

  if ( usePeriodInSecRemain <= 60 )
  {
    Led74Hc595D::Disp ( "P." );
    return false;
  }

  return true;
}

int OpticEngine::Check()
{
  return 0;
}

