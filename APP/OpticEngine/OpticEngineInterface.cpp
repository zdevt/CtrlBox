/*
 * =====================================================================================
 *
 *       Filename:  OpticEngineInterface.cpp
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

#include "OpticEngineInterface.h"
#include "Locker.h"
#include "OpticEngineDefault.h"
#include "OpticEngineThin.h"
#include "ComputerMonitor.h"
#include "OpticEngineP3A.h"
#include "OpticEngineP3A_SXGAP.h"
#include "OpticEngineCoet.h"
#include "OpticEngineP2W.h"

std::string OpticEngineInterface::m_enginename;

pthread_mutex_t OpticEngineInterface::m_OpticEngineInterfaceMutex = PTHREAD_MUTEX_INITIALIZER;

std::shared_ptr<OpticEngine> OpticEngineInterface::m_pOpticEngine = NULL;

mapGetOpticEngineObj_t OpticEngineInterface::m_mapGetOpticEngineObj =
{
  { OPTIC_ENGINE_DEFALUT_NAME,        OpticEngineDefault::GetObj },
  { OPTIC_ENGINE_THIN_NAME,           OpticEngineThin::GetObj },
  { COMPUTERMONITORNAME,           		ComputerMonitor::GetObj },
  { OPTIC_ENGINE_P3A_NAME,           	OpticEngineP3A::GetObj },
  { OPTIC_ENGINE_P3A_SXGAP_NAME,      OpticEngineP3A_SXGAP::GetObj },
  { OPTIC_ENGINE_COET_NAME,           OpticEngineCoet::GetObj },
  { OPTIC_ENGINE_P2W_NAME,           	OpticEngineP2W::GetObj },

};

OpticEngineInterface::OpticEngineInterface()
{

}

OpticEngineInterface::~OpticEngineInterface()
{

}

void OpticEngineInterface::GetSupport ( )
{
  for ( auto& ele : m_mapGetOpticEngineObj )
    PRINT_LOG2 ( "%s\n", ele.first.c_str() );
}

std::shared_ptr<OpticEngine> OpticEngineInterface::GetObj ( std::string enginename )
{
  auto iter = m_mapGetOpticEngineObj.find ( enginename );

  if ( iter != m_mapGetOpticEngineObj.end() )
    return ( iter->second ) ( enginename );

  return OpticEngineThin::GetObj ( enginename );
}

std::string OpticEngineInterface::GetEngineNameFormXml()
{
  //std::string defaultEngineType = OPTIC_ENGINE_DEFALUT_NAME;
  std::string defaultEngineType = OPTIC_ENGINE_THIN_NAME;
  //std::string defaultEngineType = COMPUTERMONITORNAME;
  XmlConfig::GetParam ( "OpticEngine", "EngineType", m_enginename, defaultEngineType );
  return m_enginename;
}

std::string OpticEngineInterface::GetEngineName ( )
{
  m_enginename = OPTIC_ENGINE_THIN_NAME;
  return m_enginename;
}

void OpticEngineInterface::Load ( ) /*  每次开机只需调用一次  原资源会自动释放 */
{
  Locker locker ( & m_OpticEngineInterfaceMutex );
  //m_pOpticEngine = GetObj ( GetEngineName() );
  m_pOpticEngine = GetObj ( GetEngineNameFormXml() );
}

std::shared_ptr<OpticEngine> OpticEngineInterface::GetEnginePtr()
{
  Locker locker ( & m_OpticEngineInterfaceMutex );
  return m_pOpticEngine;
}

