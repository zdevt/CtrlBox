/*
 * =====================================================================================
 *
 *       Filename:  InterruptHandleTask.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年09月22日 17时07分35秒
 *  Last Modified:  2015年09月22日 17时07分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <stdio.h>

#include "InterruptHandleTask.h"
#include "Common.h"
#include "Locker.h"
#include "InterruptRecvTask.h"
#include "InterruptHandleInterface.h"

pthread_mutex_t InterruptHandleTask::m_mutex = PTHREAD_MUTEX_INITIALIZER;

/*  c++11 单例方式，简洁，不需要锁 */
InterruptHandleTask* InterruptHandleTask::GetInstance()
{
  static InterruptHandleTask instance;
  return &instance;
}

InterruptHandleTask::InterruptHandleTask()
  : m_runFlag ( false )
{
  sem_init ( &m_sem, 0, 0 );

  if ( !GetRunFlag() )
  {
    SetRunFlag ( true );

    int ret, stacksize = 32 * 1024; //32K
    pthread_attr_t attr;

    ret = pthread_attr_init ( &attr );

    if ( ret != 0 )
      return;

    pthread_attr_setstacksize ( &attr, stacksize );
    pthread_create ( &m_tid, &attr, InterruptHandleTask::HandleTask, reinterpret_cast<void*> ( this ) );
    pthread_attr_destroy ( &attr );
  }
}

InterruptHandleTask::~InterruptHandleTask()
{
  if ( GetRunFlag ( ) )
  {
    SetRunFlag ( false );
    sem_wait ( &m_sem );
  }

  sem_destroy ( &m_sem );
}

bool InterruptHandleTask::GetRunFlag()
{
  return m_runFlag;
}

void InterruptHandleTask::SetRunFlag ( bool flag )
{
  m_runFlag = flag;
}

void InterruptHandleTask::_HandleTask( )
{
  std::vector<char> vecharRecv;

  while ( GetRunFlag() )
  {
    if ( InterruptRecvTask::GetInstance()->Pop ( vecharRecv ) )
    {
      if ( vecharRecv.size() >= sizeof ( interrupt_info_t ) )
      {
        interrupt_info_t* pinterrupt_info = reinterpret_cast<interrupt_info_t*> ( &vecharRecv[0] );
        InterruptHandleInterface::GetObj ( pinterrupt_info->type )->Handle (
          reinterpret_cast<void*> ( & ( pinterrupt_info->val ) ) );
      }
    }
    else
      usleep ( 100 * 1000 );
  }

  sem_post ( &m_sem );
}

void* InterruptHandleTask::HandleTask ( void* p )
{
  PTHREAD_DETACH;
  reinterpret_cast<InterruptHandleTask*> ( p )->_HandleTask();
  return NULL;
}

