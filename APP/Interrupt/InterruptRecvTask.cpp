/*
 * =====================================================================================
 *
 *       Filename:  InterruptRecvTask.cpp
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

#include "InterruptRecvTask.h"
#include "Common.h"
#include "Locker.h"

pthread_mutex_t InterruptRecvTask::m_mutex = PTHREAD_MUTEX_INITIALIZER;

InterruptRecvTask* InterruptRecvTask::GetInstance()
{
  static InterruptRecvTask instance;
  return &instance;
}

InterruptRecvTask::InterruptRecvTask()
  : m_netlink ( NETLINK_ZT ),
    m_runFlag ( false )
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
    pthread_create ( &m_tid, &attr, InterruptRecvTask::RecvTask, reinterpret_cast<void*> ( this ) );
    pthread_attr_destroy ( &attr );
  }
}

InterruptRecvTask::~InterruptRecvTask()
{
  if ( GetRunFlag ( ) )
  {
    SetRunFlag ( false );
    sem_wait ( &m_sem );
  }

  sem_destroy ( &m_sem );
}

bool InterruptRecvTask::GetRunFlag()
{
  return m_runFlag;
}

void InterruptRecvTask::SetRunFlag ( bool flag )
{
  m_runFlag = flag;
}

void InterruptRecvTask::Push ( std::vector<char> vechar )
{
  Locker locker ( &m_mutex );
  m_quectorchar.push ( vechar );
}

bool InterruptRecvTask::Pop ( std::vector<char>& vechar )
{
  Locker locker ( &m_mutex );

  if ( !m_quectorchar.empty() )
  {
    vechar = m_quectorchar.front();
    m_quectorchar.pop();
    return true;
  }

  return false;
}

void InterruptRecvTask::_RecvTask ( )
{
  std::vector<char> vecharRecv;

  while ( GetRunFlag() )
  {
    if ( 0 == m_netlink.Recv ( vecharRecv ) )
      Push ( vecharRecv );
    else
      usleep ( 50 * 1000 );
  }

  sem_post ( &m_sem );
}

void* InterruptRecvTask::RecvTask ( void* p )
{
  PTHREAD_DETACH;
  reinterpret_cast<InterruptRecvTask*> ( p )->_RecvTask();
  return NULL;
}

