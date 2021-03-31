/*
 * =====================================================================================
 *
 *       Filename:  NetCommon.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年03月27日 23时12分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include "NetCommon.h"

NetCommon::NetCommon()
{

}

NetCommon::~NetCommon()
{

}

bool NetCommon::IsLocalIp ( std::string ip )
{
  vecstr_t vecstr;

  if ( !GetAllLocalIp ( vecstr ) )
    return false;

  //for ( vecstr_t::iterator iter = vecstr.begin(); iter != vecstr.end(); ++iter )
  for ( auto ele : vecstr )
  {
    //if ( *iter == ip )
    if ( ele == ip )
      return true;
  }

  return false;
}

bool NetCommon::GetAllLocalIp ( vecstr_t& vecstr )
{
  ifaddrs* pifaddrs = NULL;
  ifaddrs* pTempifaddrs = NULL;

  void* psin_addr = NULL;
  char ipaddr[INET_ADDRSTRLEN];
  getifaddrs ( &pifaddrs );

  if ( !pifaddrs )
    return false;

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

  return true;
}

#ifdef TEST

#include <stdio.h>
#include <stdlib.h>

int main ( int argc, char* argv[] )
{
  vecstr_t vecstr;

  NetCommon::GetAllLocalIp ( vecstr );

  //for ( int i = 0; i < vecstr.size(); ++i )
  for ( auto ele : vecstr )
  {
    fprintf ( stderr, "%s \n", ele.c_str() );
  }

  fprintf ( stderr, "ok\n" );
  return 0;
}

#endif

