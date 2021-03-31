/*
 * =====================================================================================
 *
 *       Filename:  TcpAdmin.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月12日 19时45分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <algorithm>
#include <sys/prctl.h>

#include "TcpAdmin.h"
#include "Common.h"
#include "Locker.h"
#include "LogPrint.h"
#include "TcpHandleConfig.h"
#include "TcpHandleUpgrade.h"
#include "TcpHandleAlarm.h"

mapPortCnctSockHandle_t TcpAdmin::m_mapPortCnctSockHandle =
{
  { TCP_SERVER_CONFIG_PORT,   TcpHandleConfig::GetObj },
  { TCP_SERVER_ALARM_PORT,    TcpHandleAlarm::GetObj },
  { TCP_SERVER_UPGRADE_PORT,  TcpHandleUpgrade::GetObj },
};

pthread_mutex_t TcpAdmin::m_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t* TcpAdmin::GetTcpAdminMutex()
{
  return &m_mutex;
}

TcpAdmin* TcpAdmin::GetInstance()
{
  static TcpAdmin instance;
  return &instance;
}

TcpAdmin::TcpAdmin()
  : m_runFlag ( false )
{
  Init();
  Start();
}

TcpAdmin::~TcpAdmin()
{
  Stop();
  DeInit();
}

void TcpAdmin::Init()
{
  Locker locker ( &m_mutex );

  for ( auto PortHandle : m_mapPortCnctSockHandle )
  {
    lsnSock_t lsnSock = Network::MakeTCPServer ( PortHandle.first );

    if ( lsnSock > 0 )
    {
      lsnCnctInfo_t lsnCnctInfo;
      lsnCnctInfo.lsnSock = lsnSock;
      m_mapPortLsnCnctInfo.insert ( mapPortLsnCnctInfo_t::value_type ( PortHandle.first, lsnCnctInfo ) );
    }
  }

  sem_init ( &m_sem, 0, 0 );
}

void TcpAdmin::DeInit()
{
  Locker locker ( &m_mutex );

  for ( auto lsnCnctInfo : m_mapPortLsnCnctInfo )
  {
    shutdown ( (  lsnCnctInfo.second ).lsnSock, SHUT_RDWR ); /*  listen socket  */
    close ( ( lsnCnctInfo.second ).lsnSock );

    for ( auto cnctSockAddr : lsnCnctInfo.second.mapCnctSockAddr )
    {
      shutdown ( ( cnctSockAddr.first ), SHUT_RDWR ); /*  connect socket */
      close ( ( cnctSockAddr.first ) );
    }
  }

  sem_destroy ( &m_sem );
}

int TcpAdmin::Start()
{
  if ( !GetRunFlag() )
  {
    SetRunFlag ( true );
    pthread_create ( &m_tid, NULL, TcpAdmin::TcpAdminTask, reinterpret_cast<void*> ( this ) );
  }

  return 0;
}

int TcpAdmin::Stop()
{
  if ( GetRunFlag ( ) )
  {
    SetRunFlag ( false );
    sem_wait ( &m_sem );
  }

  return 0;
}

void TcpAdmin::AddConnect ( port_t port, cnctSock_t cnctSock, cnctAddr_t cnctAddr )
{
  auto portLsnCnctInfoIter = m_mapPortLsnCnctInfo.find ( port );

  if ( portLsnCnctInfoIter != m_mapPortLsnCnctInfo.end() )
    ( portLsnCnctInfoIter->second ).mapCnctSockAddr.insert ( mapCnctSockAddr_t::value_type ( cnctSock, cnctAddr ) );
}

void TcpAdmin::SetFd ( fd_set& fds )
{
  Locker locker ( &m_mutex );

  for ( auto& portLsnCnctInfo : m_mapPortLsnCnctInfo )
  {
    FD_SET ( portLsnCnctInfo.second.lsnSock, &fds );  /*  listen socket  */

    for ( auto& cnctSockAddr : portLsnCnctInfo.second.mapCnctSockAddr )
      FD_SET ( cnctSockAddr.first, &fds );  /*  connect socket */
  }
}

void TcpAdmin::HandleFd ( fd_set& fds )
{
  Locker locker ( &m_mutex );

  for ( auto portLsnCnctInfoIter = m_mapPortLsnCnctInfo.begin();
        portLsnCnctInfoIter != m_mapPortLsnCnctInfo.end(); ++portLsnCnctInfoIter )
  {
    if ( FD_ISSET ( ( portLsnCnctInfoIter->second ).lsnSock, &fds  ) ) /*  listen socket  */
    {
      sockaddr_in newConnectAddr;
      cnctSock_t cnctSock = Network::MakeAccept ( ( portLsnCnctInfoIter->second ).lsnSock,
                            reinterpret_cast<sockaddr*> ( &newConnectAddr ) );

      if ( cnctSock > 0 )
      {
        Network::SetKeepLive ( cnctSock, 6, 3, 2 );
        Network::SetNonBlock ( cnctSock );
        Network::SetNonDelay ( cnctSock );
        Network::SetLinger ( cnctSock );

        AddConnect ( portLsnCnctInfoIter->first, cnctSock, newConnectAddr );

        PRINT_LOG ( LOG_LEVEL_NORMAL, "Accept %d from(%s:%d), server(%d) totalLink=%d \n",
                    cnctSock, inet_ntoa ( newConnectAddr.sin_addr ), newConnectAddr.sin_port,
                    portLsnCnctInfoIter->first, ( int ) ( ( portLsnCnctInfoIter->second ).mapCnctSockAddr.size() ) );
      }
    }

    for ( auto cnctSockAddrIter = ( portLsnCnctInfoIter->second ).mapCnctSockAddr.begin();
          cnctSockAddrIter != ( portLsnCnctInfoIter->second ).mapCnctSockAddr.end(); )
    {
      if ( FD_ISSET ( cnctSockAddrIter->first, &fds ) )  /*  connect socket  */
      {
        /* recv && Proc data */
        auto sockHandleIter = m_mapPortCnctSockHandle.find ( portLsnCnctInfoIter->first );

        if (  ( sockHandleIter->second ) ()->HandleConnectSocket ( cnctSockAddrIter->first ) < 0 )
        {
          PRINT_LOG ( LOG_LEVEL_NORMAL, "Disconnect %d from(%s:%d), server(%d) totalLink=%d %s\n",
                      cnctSockAddrIter->first, inet_ntoa ( ( cnctSockAddrIter->second ).sin_addr ),
                      ( cnctSockAddrIter->second ).sin_port,
                      portLsnCnctInfoIter->first, ( int ) ( ( portLsnCnctInfoIter->second ).mapCnctSockAddr.size() - 1 ),
                      strerror ( errno ) );

          shutdown ( cnctSockAddrIter->first, SHUT_RDWR );
          close ( cnctSockAddrIter->first );
          ( portLsnCnctInfoIter->second ).mapCnctSockAddr.erase ( cnctSockAddrIter++ );
        }
        else
          ++cnctSockAddrIter;
      }
      else
        ++cnctSockAddrIter;
    }
  }
}

int TcpAdmin::GetMaxFd()
{
  Locker locker ( &m_mutex );

  vecsocket_t vecsocket;
  vecsocket.clear();

  for ( auto& portLsnCnctInfo : m_mapPortLsnCnctInfo )
  {
    vecsocket.push_back ( portLsnCnctInfo.second.lsnSock ) ; /*  lsnSocket  */

    for ( auto& cnctSockAddr : portLsnCnctInfo.second.mapCnctSockAddr )
      vecsocket.push_back ( cnctSockAddr.first ); /*  connect socket  */
  }

  if ( vecsocket.size() == 0 )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "vecsocket size == 0 \n" );
    return -1;
  }

  std::sort ( vecsocket.begin(), vecsocket.end() );

  return vecsocket.back();
}

void TcpAdmin::_TcpAdminTask()
{
  fd_set rdfds;
  timeval timeOut;
  int retSelect = -1;
  int maxfd = -1;

  while ( GetRunFlag() )
  {
    FD_ZERO ( &rdfds );
    SetFd ( rdfds );

    timeOut.tv_sec = 1;
    timeOut.tv_usec = 0;

    #if 0
    maxfd = GetMaxFd();

    if ( maxfd < 0 )
      continue;

    retSelect = select ( maxfd + 1, &rdfds, NULL, NULL, &timeOut );
    #else
    maxfd = FD_SETSIZE;
    retSelect = select ( maxfd, &rdfds, NULL, NULL, &timeOut );
    #endif

    if ( retSelect < 0 )
    {
      PRINT_LOG ( LOG_LEVEL_NORMAL, "retSelect = %d\n", retSelect );
      usleep ( 10 * 1000 );
    }
    else if ( retSelect == 0 )
    {
      usleep ( 10 * 1000 );
      //PRINT_LOG ( LOG_LEVEL_NORMAL, "\n" );
    }

    if ( retSelect > 0 )
      HandleFd ( rdfds );
  }

  sem_post ( &m_sem );
}

void* TcpAdmin::TcpAdminTask ( void* pObj )
{
  PTHREAD_DETACH;
  reinterpret_cast<TcpAdmin*> ( pObj )->_TcpAdminTask();
  return NULL;
}

bool TcpAdmin::GetRunFlag()
{
  return m_runFlag;
}

void TcpAdmin::SetRunFlag ( bool flag )
{
  m_runFlag = flag;
}

void TcpAdmin::SendMsgToAllLink ( port_t port, char* msg, int len )
{
  Locker locker ( &m_mutex );
  auto sockHandleIter = m_mapPortCnctSockHandle.find ( port );

  if (  sockHandleIter == m_mapPortCnctSockHandle.end() )
    return;

  pGetTcpHandleObj_t pGetTcpHandleObj = ( sockHandleIter->second );

  auto lsnCnctInfoIter = m_mapPortLsnCnctInfo.find ( port );

  if ( lsnCnctInfoIter == m_mapPortLsnCnctInfo.end() )
    return;

  for ( auto cnctSock : ( lsnCnctInfoIter->second ).mapCnctSockAddr )
    pGetTcpHandleObj()->SendData ( cnctSock.first, msg, len );
}

