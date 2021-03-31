/*
 * =====================================================================================
 *
 *       Filename:  DebugAdmin.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2015 10:08:41 AM CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <sched.h>
#include <sys/mman.h>
#include <signal.h>
#include <sys/time.h>
#include <sstream>
#include <sys/prctl.h>

#include "DebugAdmin.h"

#include "DebugHelp.h"
#include "DebugFunTest.h"
#include "DebugIpconfig.h"
#include "DebugSetMac.h"
#include "DebugIcs307.h"
#include "DebugFpgaTestPic.h"
#include "DebugI2cTestSet.h"
#include "DebugI2cTestGet.h"
#include "DebugPrintTcpData.h"
#include "DebugLightBrightnessCompensation.h"
#include "DebugGpioSet.h"
#include "DebugGpioGet.h"
#include "DebugPowerOn.h"
#include "DebugDeskTopSet.h"
#include "DebugSpiTest.h"
#include "DebugFpgaSet.h"
#include "DebugFpgaGet.h"
#include "DebugGetSupport.h"
#include "DebugSetMainboard.h"
#include "DebugSetOpticEngine.h"

/* 这里添加函数 */
funMap_t DebugAdmin::m_funMap =
{
  { "Help",      DebugHelp::GetObj },
  { "FunTest",        DebugFunTest::GetObj },
  { "Ipconfig",       DebugIpconfig::GetObj },
  { "SetMac",         DebugSetMac::GetObj },
  { "Ics307",         DebugIcs307::GetObj },
  { "FpgaTestPic",    DebugFpgaTestPic::GetObj },
  { "I2cTestSet",     DebugI2cTestSet::GetObj },
  { "I2cTestGet",     DebugI2cTestGet::GetObj },
  { "PrintTcpData",   DebugPrintTcpData::GetObj },
  { "LiBriCompen",    DebugLightBrightnessCompensation::GetObj },
  { "GpioSet",   		  DebugGpioSet::GetObj },
  { "GpioGet",   		  DebugGpioGet::GetObj },
  { "PowerOn",   		  DebugPowerOn::GetObj },
  { "DeskTopSet",  	  DebugDeskTopSet::GetObj },
  { "SpiTest",  		  DebugSpiTest::GetObj },
  { "FpgaSet",  		  DebugFpgaSet::GetObj },
  { "FpgaGet",  		  DebugFpgaGet::GetObj },
  { "GetSupport",  	  DebugGetSupport::GetObj },
  { "SetMainboard",   DebugSetMainboard::GetObj },
  { "SetOpticEngine", DebugSetOpticEngine::GetObj },
};

funMap_t& DebugAdmin::GetMap()
{
  return m_funMap;
}

void DebugAdmin::Init()
{
  for ( auto iter = m_funMap.begin(); iter != m_funMap.end(); ++iter )
    AddFun ( iter->first );
}

/*  c++11 单例方式，简洁，不需要锁 无需手动销毁 */
DebugAdmin* DebugAdmin::GetInstance()
{
  static DebugAdmin instance;
  return &instance;
}

DebugAdmin::DebugAdmin()
  : m_msg_id ( -1 ),
    m_runFlag ( false )
{
  m_msg_id = msgget ( ( key_t ) 8888, IPC_CREAT | 0666 );
  sem_init ( &m_sem, 0, 0 );

  Init();
  Start();
}

DebugAdmin::~DebugAdmin()
{
  Stop();
  sem_destroy ( &m_sem );
}

void DebugAdmin::Start()
{
  if ( !GetRunFlag() )
  {
    SetRunFlag ( true );

    int ret, stacksize = 32 * 1024; //32K
    pthread_attr_t attr;

    ret = pthread_attr_init ( &attr );

    if ( ret != 0 )
      return;

    pthread_attr_setstacksize ( &attr, stacksize );
    pthread_create ( &m_pid, &attr, DebugAdmin::DebugAdminTask, reinterpret_cast<void*> ( this ) );
    pthread_attr_destroy ( &attr );
  }
}

void DebugAdmin::Stop()
{
  if ( GetRunFlag() )
  {
    SetRunFlag ( false );
    sem_wait ( &m_sem );
  }
}

bool DebugAdmin::GetRunFlag()
{
  return m_runFlag;
}

void DebugAdmin::SetRunFlag ( bool flag )
{
  m_runFlag = flag;
}

void DebugAdmin::HandleFun ( std::string funname, std::string funarg )
{
  funMap_t::iterator iter = m_funMap.find ( funname );

  if ( iter != m_funMap.end() )
  {
    std::shared_ptr<DebugFun> p = ( iter->second ) ();

    if ( p )
      p->Fun ( funarg );
  }
}

int DebugAdmin::AddFun ( std::string funname )
{
  std::string addFunCmd;
  addFunCmd += "ln -f -s /bin/DebugAdmin /bin/";
  addFunCmd += funname;
  system ( addFunCmd.c_str() );
  return 0;
}

void DebugAdmin::StrSimplification ( std::string& str, char c )
{
  std::stringstream ssIn ( str );
  std::stringstream ssOut;
  std::string strTemp;

  while ( NULL != std::getline ( ssIn, strTemp, c ) )
  {
    if ( strTemp.size() != 0 )
      ssOut << strTemp << ' ';
  }

  str = ssOut.str();
}

void DebugAdmin::GetNameAndArg ( std::string funcmd, std::string& funname, std::string& funarg )
{
  //StrSimplification ( funcmd );
  funname.clear();
  funarg.clear();

  size_t pos = funcmd.find_first_of ( ' ' );

  if ( pos == std::string::npos )
  {
    funname = funcmd;
    funarg = " ";
  }
  else
  {
    funname.append ( funcmd.begin(), funcmd.begin() + pos );
    funarg.append ( funcmd.begin() + pos, funcmd.end() );
    pos = funarg.find_first_not_of ( ' ' );

    if ( pos != std::string::npos )
      funarg.erase ( 0, pos );
  }
}

void DebugAdmin::_DebugAdminTask()
{
  std::string funcmd, funname, funarg;

  while ( GetRunFlag() )
  {
    memset ( &m_DebugAdminMsg, 0, sizeof ( m_DebugAdminMsg ) );
    m_msg_id = msgget ( ( key_t ) 8888, IPC_CREAT | 0666 );

    if ( m_msg_id < 0 )
      continue;

    if ( -1 != msgrcv ( m_msg_id, &m_DebugAdminMsg, sizeof ( m_DebugAdminMsg ), 0, IPC_NOWAIT ) )
    {
      funcmd.clear();
      funcmd = m_DebugAdminMsg.buff;
      GetNameAndArg ( funcmd, funname, funarg );
      HandleFun ( funname, funarg );
    }

    usleep ( 200 * 1000 );
  }

  sem_post ( &m_sem );
}

void* DebugAdmin::DebugAdminTask ( void* pObj )
{
  PTHREAD_DETACH;
  DebugAdmin* pDebugAdmin = reinterpret_cast<DebugAdmin*> ( pObj );
  pDebugAdmin->_DebugAdminTask();
  return NULL;
}

