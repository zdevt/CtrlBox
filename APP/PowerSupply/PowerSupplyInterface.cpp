/*
 * =====================================================================================
 *
 *       Filename:  PowerSupplyInterface.cpp
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

#include "Locker.h"
#include "PowerSupplyInterface.h"
#include "PowerSupplyDefault.h"

std::string PowerSupplyInterface::m_PowerSupplyName;

pthread_mutex_t PowerSupplyInterface::m_PowerSupplyInterfaceMutex = PTHREAD_MUTEX_INITIALIZER;

std::shared_ptr<PowerSupply> PowerSupplyInterface::m_pPowerSupply =
  PowerSupplyDefault::GetObj ( POWERSUPPLYDEFAULTNAME );

mapGetPowerSupplyObj_t PowerSupplyInterface::m_mapGetPowerSupplyObj =
{
  { POWERSUPPLYDEFAULTNAME,        PowerSupplyDefault::GetObj },

};

PowerSupplyInterface::PowerSupplyInterface()
{

}

PowerSupplyInterface::~PowerSupplyInterface()
{

}

std::shared_ptr<PowerSupply> PowerSupplyInterface::GetObj ( std::string PowerSupplyName )
{
  auto iter = m_mapGetPowerSupplyObj.find ( PowerSupplyName );

  if ( iter != m_mapGetPowerSupplyObj.end() )
    return ( iter->second ) ( PowerSupplyName );

  return PowerSupplyDefault::GetObj ( PowerSupplyName );
}

/*  Read PowerSupplyName from EEprom or Other */
std::string PowerSupplyInterface::GetPowerSupplyName ( )
{
  m_PowerSupplyName = POWERSUPPLYDEFAULTNAME;
  return m_PowerSupplyName;
}

void PowerSupplyInterface::Load ( ) /*  每次开机只需调用一次  原资源会自动释放 */
{
  Locker locker ( & m_PowerSupplyInterfaceMutex );
  m_pPowerSupply = GetObj ( GetPowerSupplyName() );
}

std::shared_ptr<PowerSupply> PowerSupplyInterface::GetPowerSupplyPtr()
{
  Locker locker ( & m_PowerSupplyInterfaceMutex );
  return m_pPowerSupply;
}

