/*
 * =====================================================================================
 *
 *       Filename:  MainApp.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/25/2015 02:48:35 PM CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include "MainApp.h"

#include "TcpAdmin.h"
#include "DebugAdmin.h"
#include "RootfsAdmin.h"
#include "SystemDump.h"
#include "HeartBeatAdmin.h"
#include "InterruptHandleTask.h"

#include "MainboardInterface.h"
#include "ControlBoxInterface.h"
#include "PowerSupplyInterface.h"
#include "OpticEngineInterface.h"

#include "RoutineTask.h"

bool MainApp::m_runFlag = true;

void MainApp::SetRunFlag ( bool flag )
{
  m_runFlag = flag;
}

bool MainApp::GetRunFlag( )
{
  return m_runFlag;
}

MainApp::MainApp()
{
  Init();
}

MainApp::~MainApp()
{
  DeInit();
}

void MainApp::Init()
{
  sem_init ( &m_sem, 0, 0 );

  #if defined(__arm__)
  SystemDump::CatchDump();
  RootfsAdmin::CheckRootfs();
  DebugAdmin::GetInstance();
  #endif

  ControlBoxInterface::Load();
  PowerSupplyInterface::Load();
  MainboardInterface::Load();
  OpticEngineInterface::Load();

  TcpAdmin::GetInstance();
  HeartBeatAdmin::GetInstance();
  //InterruptHandleTask::GetInstance(); /*  暂时有问题 sig11退出 */

  pthread_create ( &m_tid, NULL, MainApp::MainAppTask, reinterpret_cast<void*> ( this ) );
}

void MainApp::DeInit()
{
  sem_wait ( &m_sem );
  sem_destroy ( &m_sem );
}

void* MainApp::MainAppTask ( void* pObj )
{
  PTHREAD_DETACH;
  reinterpret_cast<MainApp*> ( pObj )->_MainAppTask();
  return NULL;
}

void MainApp::_MainAppTask()
{
  while ( GetRunFlag() )
  {
    sleep ( 1 );
  }

  sem_post ( &m_sem );
}

