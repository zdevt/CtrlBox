/*
 * =====================================================================================
 *
 *       Filename:  ControlBoxInterface.cpp
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
#include "ControlBoxInterface.h"
#include "ControlBoxDefault.h"

std::string ControlBoxInterface::m_controlBoxName;

pthread_mutex_t ControlBoxInterface::m_ControlBoxInterfaceMutex = PTHREAD_MUTEX_INITIALIZER;

std::shared_ptr<ControlBox> ControlBoxInterface::m_pControlBox =
  ControlBoxDefault::GetObj ( DEFAULTCONTROLBOXNAME );

mapGetControlBoxObj_t ControlBoxInterface::m_mapGetControlBoxObj =
{
  { DEFAULTCONTROLBOXNAME,        ControlBoxDefault::GetObj },

};

ControlBoxInterface::ControlBoxInterface()
{

}

ControlBoxInterface::~ControlBoxInterface()
{

}

std::shared_ptr<ControlBox> ControlBoxInterface::GetObj ( std::string controlBoxName )
{
  auto iter = m_mapGetControlBoxObj.find ( controlBoxName );

  if ( iter != m_mapGetControlBoxObj.end() )
    return ( iter->second ) ( controlBoxName );

  return ControlBoxDefault::GetObj ( controlBoxName );
}


/*  Read controlBoxName from EEprom or Other */
std::string ControlBoxInterface::GetControlBoxName ( )
{
  /*  TODO  */
  m_controlBoxName = DEFAULTCONTROLBOXNAME;
  return m_controlBoxName;
}

void ControlBoxInterface::Load ( ) /*  每次开机只需调用一次  原资源会自动释放 */
{
  Locker locker ( & m_ControlBoxInterfaceMutex );
  m_pControlBox = GetObj ( GetControlBoxName() );
}

std::shared_ptr<ControlBox> ControlBoxInterface::GetControlBoxPtr()
{
  Locker locker ( & m_ControlBoxInterfaceMutex );
  return m_pControlBox;
}

