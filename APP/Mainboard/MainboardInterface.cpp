/*
 * =====================================================================================
 *
 *       Filename:  MainboardInterface.cpp
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
#include "MainboardInterface.h"
#include "MainboardDefault.h"
#include "MainboardMini.h"

std::string MainboardInterface::m_mainboardName;

pthread_mutex_t MainboardInterface::m_MainboardInterfaceMutex = PTHREAD_MUTEX_INITIALIZER;

std::shared_ptr<Mainboard> MainboardInterface::m_pMainboard =
  MainboardDefault::GetObj ( MAINBOARDDEFAULTNAME );

mapGetMainboardObj_t MainboardInterface::m_mapGetMainboardObj =
{
  { MAINBOARDDEFAULTNAME,     MainboardDefault::GetObj },
  { MAINBOARDMININAME,        MainboardMini::GetObj },

};

MainboardInterface::MainboardInterface()
{

}

MainboardInterface::~MainboardInterface()
{

}

void MainboardInterface::GetSupport ( )
{
  for ( auto& ele : m_mapGetMainboardObj )
    PRINT_LOG2 ( "%s\n", ele.first.c_str() );
}

std::shared_ptr<Mainboard> MainboardInterface::GetObj ( std::string mainboardName )
{
  auto iter = m_mapGetMainboardObj.find ( mainboardName );

  if ( iter != m_mapGetMainboardObj.end() )
    return ( iter->second ) ( mainboardName );

  return MainboardDefault::GetObj ( mainboardName );
}

/*  Read mainboardName from EEprom or Other */
std::string MainboardInterface::GetMainboardName ( )
{
  //m_mainboardName = MAINBOARDDEFAULTNAME;
  m_mainboardName = MAINBOARDMININAME;
  return m_mainboardName;
}

std::string MainboardInterface::GetMainboardNameFormXml()
{
  std::string defaultMainboardName = MAINBOARDMININAME;
  XmlConfig::GetParam ( "Mainboard", "Model", m_mainboardName, defaultMainboardName );
  return m_mainboardName;
}

void MainboardInterface::Load ( ) /*  每次开机只需调用一次  原资源会自动释放 */
{
  Locker locker ( & m_MainboardInterfaceMutex );
  //m_pMainboard = GetObj ( GetMainboardName() );
  m_pMainboard = GetObj ( GetMainboardNameFormXml() );
  m_pMainboard->Init();
}

std::shared_ptr<Mainboard> MainboardInterface::GetMainboardPtr()
{
  Locker locker ( & m_MainboardInterfaceMutex );
  return m_pMainboard;
}

