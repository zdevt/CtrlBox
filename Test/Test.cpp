/*
 * =====================================================================================
 *
 *       Filename:  Test.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年03月27日 17时16分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */


#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>
#include <ifaddrs.h>

typedef std::vector<std::string> vecstr_t;

void GetAllLocalIp ( vecstr_t& vecstr )
{
  ifaddrs* pifaddrs = NULL;
  ifaddrs* pTempifaddrs = NULL;

  void* psin_addr = NULL;
  char ipaddr[128];
  getifaddrs ( &pifaddrs );

  if ( !pifaddrs )
    return;

  pTempifaddrs = pifaddrs;

  while ( pTempifaddrs != NULL )
  {
    if ( pTempifaddrs->ifa_addr->sa_family == AF_INET )
    {
      psin_addr = & ( ( ( sockaddr_in* ) ( pTempifaddrs->ifa_addr ) )->sin_addr );
      inet_ntop ( AF_INET, psin_addr, ipaddr, INET_ADDRSTRLEN );
      vecstr.insert ( vecstr.begin(), ipaddr );
    }
    pTempifaddrs = pTempifaddrs->ifa_next;
  }

  freeifaddrs ( pifaddrs );
}

void test2()
{
  //#ifndef __i386__
#if !defined(__i386__) && !defined(__x86_64__)
  fprintf ( stderr, "arm\n" );
#else
  fprintf ( stderr, "pc\n" );
#endif

}

int main ( int argc, char* argv[] )
{
  test2();

  return 0;
}


