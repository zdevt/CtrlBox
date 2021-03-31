/*
 * =====================================================================================
 *
 *       Filename:  GetNetWork.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/11/2015 11:09:30 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GetNetWork.h"


GetNetWork::GetNetWork()
{

}

GetNetWork::~GetNetWork()
{

}

bool GetNetWork::GetIp ( std::string& ip, std::string& mask )
{
  char buffer[32];

  memset ( buffer, 0, 32 );
  FILE* fp = popen ( "ifconfig | grep inet | grep -v inet6 | cut -d \":\" -f2 | cut -d \" \" -f1 | grep -v \"127.0.0.1\"", "r" );

  if ( !fp )
    return false;

  fgets ( buffer, 32, fp );
  pclose ( fp );

  ip = buffer;

  memset ( buffer, 0, 32 );
  fp = popen ( "ifconfig | grep inet | grep -v inet6 | grep -v \"127.0.0.1\" | cut -d \":\" -f4 | head -n 1", "r" );

  if ( !fp )
    return false;

  fgets ( buffer, 32, fp );
  pclose ( fp );

  mask = buffer;

  return true;
}

bool GetNetWork::GetMac ( std::string& mac )
{
  char buffer[32];

  memset ( buffer, 0, 32 );
  FILE* fp = popen ( "ifconfig | grep HWaddr | awk '{print $5}'", "r" );

  if ( !fp )
    return false;

  fgets ( buffer, 32, fp );
  pclose ( fp );

  mac = buffer;
  return true;
}

bool GetNetWork::GetGateWay ( std::string& gw )
{
  char buffer[32];

  memset ( buffer, 0, 32 );
  FILE* fp = popen ( "ip route | grep default | cut -d ' ' -f3", "r" );

  if ( !fp )
    return false;

  fgets ( buffer, 32, fp );
  pclose ( fp );

  gw = buffer;

  return true;
}

#ifdef TEST

int main ( int argc, char* argv[] )
{
  std::string ip, mask, mac, gw;

  GetNetWork::GetIp ( ip, mask );
  fprintf ( stderr, "%s %s\n", ip.c_str(), mask.c_str() );

  GetNetWork::GetMac ( mac );
  fprintf ( stderr, "%s\n", mac.c_str() );

  GetNetWork::GetGateWay ( gw );
  fprintf ( stderr, "%s\n", gw.c_str() );
  return 0;
}

#endif

