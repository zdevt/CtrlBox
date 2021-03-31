/*
 * =====================================================================================
 *
 *       Filename:  HeartBeatAdmin.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年03月25日 10时15分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "CommunicateProtocol.h"
#include "HeartBeatAdmin.h"
#include "NetCommon.h"


HeartBeatAdmin::HeartBeatAdmin()
  : m_heartBeatServerPort ( HEARTBEAT_REMOTE_PORT ),
    m_heartBeatServerListenSock ( -1 ),
    m_udpRemoteport ( 7000 ),
    m_udpServerPort ( 8000 )
{
  Init();
}

HeartBeatAdmin::~HeartBeatAdmin()
{
  DeInit();
}

int HeartBeatAdmin::Init()
{
  m_heartBeatServerListenSock = Network::MakeTCPServer ( m_heartBeatServerPort );

  m_SendBroadcastSock = Network::MakeBcClient();
  Network::SetSockAddr ( &m_SendBroadcastAddr, m_udpRemoteport );

  m_udpRecvBroadcastSock = Network::MakeUDPServer ( m_udpServerPort );

  if ( m_heartBeatServerListenSock > 0 )
    pthread_create ( &m_tid, NULL, HeartBeatAdmin::HeartBeatTask, this );

  pthread_create ( &m_tid, NULL, HeartBeatAdmin::RecvBroadCastTask, this );

  return 0;
}

int HeartBeatAdmin::DeInit()
{
  if ( m_heartBeatSock > 0 )
  {
    shutdown ( m_heartBeatServerListenSock, SHUT_RDWR );
    close ( m_heartBeatServerListenSock );
    m_heartBeatServerListenSock = -1;
  }

  return 0;
}

void* HeartBeatAdmin::HeartBeatTask ( void* p )
{
  PTHREAD_DETACH;
  HeartBeatAdmin* p1 = reinterpret_cast<HeartBeatAdmin*> ( p );
  p1->_Task();
  return NULL;
}

void* HeartBeatAdmin::RecvBroadCastTask ( void* p  )
{
  PTHREAD_DETACH;
  HeartBeatAdmin* p1 = reinterpret_cast<HeartBeatAdmin*> ( p );
  p1->_Task2();
  return NULL;
}

int HeartBeatAdmin::_Task2()
{
  sockaddr_in m_heartBeatAddr;
  int heartBeatAddrLen;
  std::vector<char> vecharRecv, vecharSend;
  vecharRecv.resize ( sizeof ( MCP_HEADER_t ), 0  );

  vecharSend.resize ( sizeof ( MCP_HEADER_t ) + MCP_ADDR_LEN, 0  );
  uint32_t recvLen = 0;
  uint32_t sndLen = 0;

  while ( 1 )
  {
    recvLen = Network::RecvFrom ( m_udpRecvBroadcastSock, &vecharRecv[0], vecharRecv.size(), 0,
                                  reinterpret_cast<sockaddr*> ( &m_heartBeatAddr ),
                                  reinterpret_cast<socklen_t*> ( &heartBeatAddrLen ) );

    if ( recvLen > 0 )
    {
      fprintf ( stderr, "UDP recvLen = %d\n", recvLen );

      MCP_HEADER_t* p = reinterpret_cast<MCP_HEADER_t*> ( &vecharSend[0] );
      p->mcp_subtype = MCP_RET_GET_CTRLSERVERIP;
      memcpy ( ( p->mcp_data ), "10.1.18.89", strlen ( "10.1.18.89" ) );
      sndLen = Network::SendTo  ( m_SendBroadcastSock, &vecharSend[0], vecharSend.size(), MSG_NOSIGNAL,
                                  reinterpret_cast<sockaddr*> ( &m_SendBroadcastAddr ), sizeof ( m_SendBroadcastAddr ) );
    }
    else
      sleep ( 5 );
  }

  return 0;
}

int HeartBeatAdmin::_Task()
{
  u_int32_t recvLen = 0;
  u_int32_t sendLen = 0;
  std::string serverip;

  std::vector<char> vecharRecv, vecharSend;

  vecharRecv.resize ( sizeof ( MCP_HEADER_t ), 0  );
  vecharSend.resize ( sizeof ( MCP_HEADER_t ), 0  );
  MCP_HEADER_t* pMCP_HEADER = reinterpret_cast< MCP_HEADER_t*> ( &vecharSend[0] );

  fd_set rdfds;
  timeval timeOut;
  int retSelect = -1;
  int maxfd = -1;
  int clientSock = -1;

  while ( 1 )
  {
    FD_ZERO ( &rdfds );
    FD_SET ( m_heartBeatServerListenSock, &rdfds ); /*  connect socket */
    timeOut.tv_sec = 1;
    timeOut.tv_usec = 0;
    maxfd = m_heartBeatServerListenSock + 1;
    retSelect = select ( maxfd + 1, &rdfds, NULL, NULL, &timeOut );

    if ( retSelect <= 0 )
      continue;

    clientSock = Network::MakeAccept ( m_heartBeatServerListenSock );

    if ( clientSock > 0 )
      fprintf ( stderr, "clientSock = %d\n", clientSock );
    else
      return 0;

    while ( 1 )
    {
      sendLen = Network::Sendn ( clientSock, &vecharSend[0], vecharSend.size() );

      if ( sendLen > 0 )
      {
        fprintf ( stderr, "sendLen = %d\n", sendLen );
        sleep ( 3 );
        recvLen = Network::Recvn ( clientSock, &vecharRecv[0], vecharRecv.size() );
        fprintf ( stderr, "recvLen= %d\n", recvLen );
      }
      else
        return 0;
    }
  }

  return 0;
}

#ifdef TEST

int main ( int argc, char* argv[] )
{
  HeartBeatAdmin a;

  while ( 1 )
  {
    sleep ( 1 );
  }

  return 0;
}

#endif

