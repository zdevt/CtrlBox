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
#include <error.h>
#include <sys/ioctl.h>

#include "CommunicateProtocol.h"
#include "HeartBeatAdmin.h"
#include "NetCommon.h"
#include "LogPrint.h"


bool HeartBeatAdmin::m_serverok = false;

HeartBeatAdmin* HeartBeatAdmin::GetInstance()
{
  static HeartBeatAdmin instance;
  return &instance;
}

bool HeartBeatAdmin::GetServerOkFlag()
{
  return m_serverok;
}

void HeartBeatAdmin::SetServerOkFlag ( bool flag )
{
  m_serverok = flag;
}

HeartBeatAdmin::HeartBeatAdmin()
  : m_broadcastPort ( BROADCAST_PORT ),
    m_broadcastSock ( -1 ),
    m_udpServerPort ( UDPSERVER_PORT ),
    m_udpServerSock ( -1 ),
    m_heartBeatServerPort ( HEARTBEAT_REMOTE_PORT ),
    m_heartBeatSock ( -1 ),
    m_runFlag ( false )

{
  Init();
}

HeartBeatAdmin::~HeartBeatAdmin()
{
  DeInit();
}

int HeartBeatAdmin::Init()
{
  m_broadcastSock = Network::MakeBcClient();
  Network::SetSockAddr ( &m_broadcastAddr, m_broadcastPort );

  m_udpServerSock = Network::MakeUDPServer ( m_udpServerPort );

  if ( ( m_broadcastSock > 0 ) && ( m_udpServerSock > 0 ) )
  {
    int ret, stacksize = 32 * 1024; //32K
    pthread_attr_t attr;

    ret = pthread_attr_init ( &attr );

    if ( ret != 0 )
      return -1;

    pthread_attr_setstacksize ( &attr, stacksize );
    pthread_create ( &m_tid, &attr, HeartBeatAdmin::HeartBeatTask, this );
    pthread_attr_destroy ( &attr );
  }

  return 0;
}

int HeartBeatAdmin::DeInit()
{
  if ( m_broadcastSock > 0 )
  {
    shutdown ( m_broadcastSock, SHUT_RDWR );
    close ( m_broadcastSock );
    m_broadcastSock = -1;
  }

  if ( m_udpServerSock > 0 )
  {
    shutdown ( m_udpServerSock, SHUT_RDWR );
    close ( m_udpServerSock );
    m_udpServerSock = -1;
  }

  if ( m_heartBeatSock > 0 )
  {
    shutdown ( m_heartBeatSock, SHUT_RDWR );
    close ( m_heartBeatSock );
    m_heartBeatSock = -1;
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
  int t = 0;

  while ( 1 )
  {
    if ( !GetServerOkFlag() )
    {
      if ( FindCtrlServer ( serverip ) )
      {
        m_heartBeatSock = Network::MakeTCPClient ( serverip.c_str(), m_heartBeatServerPort, 3000 );

        if ( m_heartBeatSock > 0 )
        {
          Network::SetKeepLive ( m_heartBeatSock, 6, 3, 2 );
          Network::SetNonBlock ( m_heartBeatSock );
          Network::SetNonDelay ( m_heartBeatSock );
          Network::SetLinger ( m_heartBeatSock );
          SetServerOkFlag ( true );
        }
        else
        {
          //PRINT_LOG ( LOG_LEVEL_NORMAL, "Connect Heartbeat Server Error!\n" );
          usleep ( 3000 * 1000 ); /*  connect error sleep 3 */
        }
      }
      else
      {
        usleep ( 3000 * 1000 );
      }
    }
    else
    {
      FD_ZERO ( &rdfds );
      FD_SET ( m_heartBeatSock, &rdfds );  /*  connect socket */
      timeOut.tv_sec = 1;
      timeOut.tv_usec = 0;
      maxfd = m_heartBeatSock + 1;
      retSelect = select ( maxfd, &rdfds, NULL, NULL, &timeOut );

      if ( ++t > 120 )
      {
        //连续120秒没有收到心跳包
        SetServerOkFlag ( false );
        shutdown ( m_heartBeatSock, SHUT_RDWR );
        close ( m_heartBeatSock );
        m_heartBeatSock = -1;
        t = 0;
        continue;
      }

      if ( retSelect == 0 )
      {
        usleep ( 50 * 1000 );
        continue;
      }
      else if ( retSelect < 0 )
      {
        PRINT_LOG ( LOG_LEVEL_NORMAL, "select < 0, error(%d):%s\n", errno, strerror ( errno ) );
      }

      /*  Recv Heart Beart From Ctrl Server  */
      recvLen = Network::Recvn ( m_heartBeatSock, &vecharRecv[0], vecharRecv.size() ); /*  timeout 5s  */

      if ( ( recvLen == ( uint32_t ) ( -1 ) ) && ( errno == EAGAIN ) )
      {
        PRINT_LOG ( LOG_LEVEL_NORMAL, "read failed, errstr is: %s\n", strerror ( errno ) );
        continue;
      }

      t = 0;

      if ( recvLen != vecharRecv.size() ) /* Get Resp timeout Close sock */
      {
        PRINT_LOG ( LOG_LEVEL_NORMAL, "socket %d recvLen = %d, error(%d): %s\n",
                    m_heartBeatSock, recvLen, errno, strerror ( errno ) );

        SetServerOkFlag ( false );
        shutdown ( m_heartBeatSock, SHUT_RDWR );
        close ( m_heartBeatSock );
        m_heartBeatSock = -1;
      }
      else
      {
        memcpy ( &vecharSend[0], &vecharRecv[0], sizeof ( MCP_HEADER_t ) );
        pMCP_HEADER->mcp_type = MCP_RETURN;
        pMCP_HEADER->mcp_subtype = MCP_RET_GET_ONLINESTATE;
        sendLen = Network::Sendn ( m_heartBeatSock, &vecharSend[0], vecharSend.size() );

        /*  发送失败也关闭 */
        if ( sendLen != vecharSend.size() )
        {
          PRINT_LOG ( LOG_LEVEL_NORMAL, "socket %d sendLen = %d, error(%d): %s\n",
                      m_heartBeatSock, sendLen, errno, strerror ( errno ) );

          SetServerOkFlag ( false );
          shutdown ( m_heartBeatSock, SHUT_RDWR );
          close ( m_heartBeatSock );
          m_heartBeatSock = -1;
        }
      }

      /*  此时收到其他单元的广播包，只收数据不处理，解决RECV-Q 阻塞问题 */
      {
        int recvAddrLen = sizeof ( m_heartBeatAddr );
        #if 0
        RecvFrom ( m_udpServerSock, &vecharRecv[0], vecharRecv.size(),
                   reinterpret_cast<sockaddr*> ( &m_heartBeatAddr ),
                   reinterpret_cast<socklen_t*> ( &recvAddrLen ) );
        #else
        RecvAllOnce ( m_udpServerSock, &vecharRecv[0], vecharRecv.size(),
                      reinterpret_cast<sockaddr*> ( &m_heartBeatAddr ),
                      reinterpret_cast<socklen_t*> ( &recvAddrLen ) );
        #endif
      }
    }
  }

  return 0;
}

int HeartBeatAdmin::RecvAllOnce ( int sockfd, void* vptr, ssize_t n, struct sockaddr* addr, socklen_t* len )
{
  while ( RecvFrom ( sockfd, vptr, n, addr, len ) > 0 );

  return 0;
}

int HeartBeatAdmin::RecvFrom ( int sockfd, void* vptr, ssize_t n, struct sockaddr* addr, socklen_t* len )
{
  fd_set rdfds;
  FD_ZERO ( &rdfds );
  FD_SET ( sockfd, &rdfds );

  timeval timeOut;
  timeOut.tv_sec  = 0;
  timeOut.tv_usec = 100 * 1000;

  int retSelect = select ( sockfd + 1, &rdfds, NULL, NULL, &timeOut );

  if ( retSelect > 0 )
    return Network::RecvFrom ( sockfd, vptr, n, 0, addr, len );

  return retSelect;
}

bool HeartBeatAdmin::FindCtrlServer ( std::string& serverip )
{
  bool bRet = false;

  std::vector<char> vechar;
  vechar.resize ( sizeof ( MCP_HEADER_t ), 0 );

  MCP_HEADER_t* pMCP_HEADER  = reinterpret_cast<MCP_HEADER_t*> ( &vechar[0] );
  pMCP_HEADER->mcp_magicword = MCP_MAGICWORD;
  pMCP_HEADER->mcp_type      = MCP_COMMAND;
  pMCP_HEADER->mcp_subtype   = MCP_CMD_GET_CTRLSERVERIP;

  /*  Send Get Server Ip Request */
  u_int32_t sndLen = Network::SendTo  ( m_broadcastSock, &vechar[0], vechar.size(), MSG_NOSIGNAL,
                                        reinterpret_cast<sockaddr*> ( &m_broadcastAddr ), sizeof ( m_broadcastAddr ) );

  if ( sndLen != vechar.size() )
    return bRet;

  std::vector<char> vecharRecv;
  vecharRecv.resize ( sizeof ( MCP_HEADER_t ) + MCP_ADDR_LEN, 0  );

  /*  Get Ctrl Server IP */
  bool skipSelfIpflag = false;
  fd_set rdfds;
  int heartBeatAddrLen = sizeof ( m_heartBeatAddr );
  char ipaddr[INET_ADDRSTRLEN] = "";

  while ( !skipSelfIpflag )
  {
    FD_ZERO ( &rdfds );
    FD_SET ( m_udpServerSock, &rdfds );

    timeval timeOut;

    timeOut.tv_sec  = 0;
    timeOut.tv_usec = 500;

    int retSelect = select ( m_udpServerSock + 1, &rdfds, NULL, NULL, &timeOut );

    if ( retSelect > 0 )
    {
      u_int32_t recvLen = Network::RecvFrom ( m_udpServerSock, &vecharRecv[0], vecharRecv.size(), 0,
                                              reinterpret_cast<sockaddr*> ( &m_heartBeatAddr ),
                                              reinterpret_cast<socklen_t*> ( &heartBeatAddrLen ) );

      strncpy ( ipaddr, inet_ntoa ( m_heartBeatAddr.sin_addr ), INET_ADDRSTRLEN );

      #if defined(__arm__)

      if ( !NetCommon::IsLocalIp ( ipaddr ) )
      #endif
      {
        if ( recvLen != ( sizeof ( MCP_HEADER_t ) + MCP_ADDR_LEN ) && recvLen != sizeof ( MCP_HEADER_t ) )
        {
          PRINT_LOG ( LOG_LEVEL_NORMAL, "Illegal receive datalen %d, broadcast from %s\n", recvLen, ipaddr );
          continue;
        }

        MCP_HEADER_t* p = reinterpret_cast<MCP_HEADER_t*> ( &vecharRecv[0] );

        if ( p->mcp_subtype != MCP_RET_GET_CTRLSERVERIP )
        {
          PRINT_LOG ( LOG_LEVEL_NORMAL, "Subtype is %d, broadcast from %s\n", p->mcp_subtype, ipaddr );
          continue;
        }

        serverip = reinterpret_cast<char*> ( p->mcp_data );
        PRINT_LOG ( LOG_LEVEL_NORMAL, "ipaddr=%s serverip=%s\n", ipaddr, serverip.c_str() );
        bRet = true;

        break;
      }
    }
    else
    {
      break;
    }
  }

  return bRet;
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

