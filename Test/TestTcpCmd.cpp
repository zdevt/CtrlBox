/*
 * =====================================================================================
 *
 *       Filename:  TestTcpCmd.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/12/2015 12:51:03 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include <pthread.h>
#include <semaphore.h>

#include <vector>
#include <string.h>
#include <strings.h>

#include "../APP/Common/CommunicateProtocol.h"


int SendTcpData ( const char* ip, const char* port, char* buffer, int len )
{
  sockaddr_in serveraddr;

  unsigned short sport = 0;
  sscanf ( port, "%d", &sport );

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr ( ip );
  serveraddr.sin_port = htons ( sport );
  int serlen = sizeof ( serveraddr );

  int s = socket ( AF_INET, SOCK_STREAM, 0 );
  fprintf ( stderr, "socket = %d\n", s );

  int wr = 0;

  if ( 0 != connect ( s, reinterpret_cast<sockaddr*> ( &serveraddr ), serlen ) )
  {
    shutdown ( s, SHUT_RDWR );
    close ( s );
    fprintf ( stderr, "connect error! %s\n", strerror ( errno ) );
    return -1;
  }

  wr = write ( s, buffer, len );
  fprintf ( stderr, "write %s\n", strerror ( errno ) );

  fd_set rdfds;
  timeval timeOut;
  bool runFlag = true;

  int ret = -1;
  int rdLen = 0;
  int nToRead = 0;
  int i = 0;
  char recvb[128] = { 0 };

  while ( runFlag )
  {
    FD_ZERO ( &rdfds );
    FD_SET ( s, &rdfds );

    timeOut.tv_sec = 1;
    timeOut.tv_usec = 0;

    ret = select ( s + 1, &rdfds, NULL, NULL, &timeOut );
    if ( 0 == ret )
    {
      i++;
      if ( i == 3 )
        runFlag = true;
      //runFlag = false;
      continue;
    }
    else if ( ret < 0 )
    {
      fprintf ( stderr, "select error ret=%d errno=%d %s\n", ret, errno, strerror ( errno ) );
      runFlag = false;
    }
    else
    {
      ioctl ( s, FIONREAD, &nToRead );
      rdLen = recv ( s, recvb, nToRead, 0 );
      if ( rdLen > 0 )
        fprintf ( stderr, "read=%d %s\n", rdLen, recvb + 16 );
      else
        runFlag = false;
      i = 0;
    }
  }

  shutdown ( s, SHUT_RDWR );
  close ( s );

  return 0;
}


int main ( int argc, char* argv[] )
{
  char p[12] = { 1, 1, 1, 1};
  char p2[48];
  char p3[48];

  memset ( p, 0xa5, 12 );
  std::vector<char> vechar;

  MCP_HEADER_t* pM = reinterpret_cast<MCP_HEADER_t*> ( p2 );
  MCP_HEADER_t* pM2 = reinterpret_cast<MCP_HEADER_t*> ( p3 );

  pM->mcp_magicword = 0xeb90;
  pM->mcp_id = 0x1234;
  pM->mcp_type = 0x1;
  pM->mcp_subtype = 0x1;
  pM->mcp_status = 0;
  pM->mcp_datalen = 3;
  pM->mcp_data[0] = 0x3;
  pM->mcp_data[1] = 0x1;
  pM->mcp_data[2] = 0x2;

  pM2->mcp_magicword = 0xeb90;
  pM2->mcp_id = 0x1234;
  pM2->mcp_type = 0x1;
  pM2->mcp_subtype = 0x2;
  pM2->mcp_status = 0;
  pM2->mcp_datalen = 0;

  vechar.insert ( vechar.end(), p, p + 12 );
  vechar.insert ( vechar.end(), p2, p2 + 48 );
  vechar.insert ( vechar.end(), p, p + 12 );
  vechar.insert ( vechar.end(), p3, p3 + 48 );

  if ( argc == 3 )
    SendTcpData ( argv[1], argv[2], &vechar[0], vechar.size() );
  else
    SendTcpData ( "127.0.0.1", "10002", &vechar[0], vechar.size() );

  return 0;
}


