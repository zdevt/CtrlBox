/*
 * =====================================================================================
 *
 *       Filename:  NetLink.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/21/2015 01:52:28 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "NetLink.h"

int NetLink::m_netlinkSocket = -1;

NetLink::NetLink ( int protocolType )
  : m_protocolType ( protocolType )
{
  Init();
}


NetLink::~NetLink()
{
  DeInit();
}


int NetLink::Init()
{
  if ( m_netlinkSocket > 0 )
    return 0;

  m_netlinkSocket = socket ( AF_NETLINK, SOCK_RAW, m_protocolType );

  if ( m_netlinkSocket < 0 )
    return ERROR_NETLINK_SOCKET;

  bzero ( &m_sockaddr_nl, sizeof ( m_sockaddr_nl ) );
  m_sockaddr_nl.nl_family = AF_NETLINK;
  m_sockaddr_nl.nl_pid = getpid();
  m_sockaddr_nl.nl_groups = 0; /* multi cast */

  if ( bind ( m_netlinkSocket, reinterpret_cast<sockaddr*> ( &m_sockaddr_nl ), sizeof ( m_sockaddr_nl ) ) < 0 )
  {
    fprintf ( stderr, "ERROR_NETLINK_BIND\n" );
    shutdown ( m_netlinkSocket, SHUT_RDWR );
    close ( m_netlinkSocket );
    m_netlinkSocket = -1;
    return ERROR_NETLINK_BIND;
  }

  return 0;
}

int NetLink::DeInit()
{
  if ( m_netlinkSocket > 0 )
  {
    shutdown ( m_netlinkSocket, SHUT_RDWR );
    close ( m_netlinkSocket );
    m_netlinkSocket = -1;
  }

  return 0;
}

int NetLink::Send ( std::vector<char> vecharSend, int msgType, pthread_t despid )
{
  return Send ( &vecharSend[0], vecharSend.size(), msgType, despid );
}

int NetLink::Send ( char* buffer, int len, int msgType, pthread_t despid )
{
  if ( len <= 0 )
    return ERROR_NETLINK_BUFFER;

  if ( m_netlinkSocket < 0 )
    return ERROR_NETLINK_SOCKET;

  sockaddr_nl sockaddr_nl_dest;
  nlmsghdr* pNlmsghdr = NULL;
  iovec iovec_nl;
  msghdr msghdr_nl;  /* sendmsg need */

  std::vector<char> vechar;
  vechar.resize ( NLMSG_SPACE ( MAX_PAYLOAD ), 0 );
  pNlmsghdr = reinterpret_cast<nlmsghdr*> ( &vechar[0] );

  memcpy ( NLMSG_DATA ( pNlmsghdr ), buffer, len );
  pNlmsghdr->nlmsg_len        = NLMSG_LENGTH ( len );
  pNlmsghdr->nlmsg_pid        = getpid();
  pNlmsghdr->nlmsg_type       = msgType;
  pNlmsghdr->nlmsg_flags      = 0;

  iovec_nl.iov_base           = reinterpret_cast<void*> ( pNlmsghdr );
  iovec_nl.iov_len            = pNlmsghdr->nlmsg_len;

  bzero ( &sockaddr_nl_dest, sizeof ( sockaddr_nl_dest ) );
  sockaddr_nl_dest.nl_family  = AF_NETLINK;
  sockaddr_nl_dest.nl_pid     = despid;
  sockaddr_nl_dest.nl_groups  = 0;

  msghdr_nl.msg_name          = reinterpret_cast<void*> ( &sockaddr_nl_dest );
  msghdr_nl.msg_namelen       = sizeof ( sockaddr_nl_dest );
  msghdr_nl.msg_iov           = &iovec_nl;
  msghdr_nl.msg_iovlen        = 1; /* Number of elements in the vector.  */
  msghdr_nl.msg_control       = NULL;
  msghdr_nl.msg_controllen    = 0;

  if ( sendmsg ( m_netlinkSocket, const_cast<const msghdr*> ( &msghdr_nl ), MSG_NOSIGNAL ) < 0 )
    return ERROR_NETLINK_SEND;

  return 0;
}

int NetLink::Recv ( std::vector<char>& vecharRecv )
{
  if ( m_netlinkSocket < 0 )
    return ERROR_NETLINK_SOCKET;

  sockaddr_nl sockaddr_nl_dest;
  nlmsghdr* pNlmsghdr;
  iovec iovec_nl;
  msghdr msghdr_nl;  /* sendmsg need */

  std::vector<char> vechar;
  vechar.resize ( NLMSG_SPACE ( MAX_PAYLOAD ), 0 );
  pNlmsghdr = reinterpret_cast<nlmsghdr*> ( &vechar[0] );

  iovec_nl.iov_base           = reinterpret_cast<void*> ( pNlmsghdr );
  iovec_nl.iov_len            = NLMSG_SPACE ( MAX_PAYLOAD );

  bzero ( &sockaddr_nl_dest, sizeof ( sockaddr_nl_dest ) );
  msghdr_nl.msg_name          = reinterpret_cast<void*> ( &sockaddr_nl_dest );
  msghdr_nl.msg_namelen       = sizeof ( sockaddr_nl_dest );
  msghdr_nl.msg_iov           = &iovec_nl;
  msghdr_nl.msg_iovlen        = 1; /* Number of elements in the vector.  */
  msghdr_nl.msg_control       = NULL;
  msghdr_nl.msg_controllen    = 0;

  if ( recvmsg ( m_netlinkSocket, &msghdr_nl, 0 ) < 0 )
    return ERROR_NETLINK_RECV;

  int len = ( int ) ( pNlmsghdr->nlmsg_len - NLMSG_HDRLEN );
  vecharRecv.resize ( len, 0 );

  memcpy ( &vecharRecv[0], NLMSG_DATA ( pNlmsghdr ), len );

  return 0;
}

int NetLink::Recv ( char* buffer, int& len )
{
  if ( m_netlinkSocket < 0 )
    return ERROR_NETLINK_SOCKET;

  sockaddr_nl sockaddr_nl_dest;
  nlmsghdr* pNlmsghdr;
  iovec iovec_nl;
  msghdr msghdr_nl;  /* sendmsg need */

  std::vector<char> vechar;
  vechar.resize ( NLMSG_SPACE ( MAX_PAYLOAD ), 0 );
  pNlmsghdr = reinterpret_cast<nlmsghdr*> ( &vechar[0] );

  iovec_nl.iov_base           = reinterpret_cast<void*> ( pNlmsghdr );
  iovec_nl.iov_len            = NLMSG_SPACE ( MAX_PAYLOAD );

  bzero ( &sockaddr_nl_dest, sizeof ( sockaddr_nl_dest ) );
  msghdr_nl.msg_name          = reinterpret_cast<void*> ( &sockaddr_nl_dest );
  msghdr_nl.msg_namelen       = sizeof ( sockaddr_nl_dest );
  msghdr_nl.msg_iov           = &iovec_nl;
  msghdr_nl.msg_iovlen        = 1; /* Number of elements in the vector.  */
  msghdr_nl.msg_control       = NULL;
  msghdr_nl.msg_controllen    = 0;

  if ( recvmsg ( m_netlinkSocket, &msghdr_nl, 0 ) < 0 )
    return ERROR_NETLINK_RECV;

  len = ( int ) ( pNlmsghdr->nlmsg_len - NLMSG_HDRLEN );
  memcpy ( buffer, NLMSG_DATA ( pNlmsghdr ), len );

  return 0;
}

#ifdef TEST
#include <string>

int main ( int argc, char* argv[] )
{
  NetLink a ( NETLINK_ZT );

  char buffer[32] ;
  memset ( buffer, 0, 32 );
  strncpy ( buffer, "This is a msg from user", 32 );
  a.Send ( buffer, strlen ( buffer ) + 1 );
  char recvBuffer[2048] = { 0 };
  int recvLen = 0;

  a.Recv ( recvBuffer, recvLen );
  fprintf ( stderr, "Kernel->%d %s\n", recvLen, recvBuffer );

  irq_opt_t* p = new irq_opt_t[4];
  p[0].irqNo = 0;
  p[0].status = 0;
  p[1].irqNo = 0;
  p[1].status = 1;
  p[2].irqNo = 0;
  p[2].status = 0;
  p[3].irqNo = 0;
  p[3].status = 1;
  a.Send ( reinterpret_cast<char*> ( p ), sizeof ( irq_opt_t ) * 4, MSG_TYPE_ENABLE );
  a.Recv ( recvBuffer, recvLen );
  fprintf ( stderr, "Kernel->%d %s\n", recvLen, recvBuffer );

  delete[] p;

  return 0;
}

#endif


