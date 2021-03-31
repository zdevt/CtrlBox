/*
 * =====================================================================================
 *
 *       Filename:  SetNetWork.cpp
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

#include "SetNetWork.h"
#include "XmlConfig.h"
#include "Locker.h"

pthread_mutex_t SetNetWork::m_Mutex = PTHREAD_MUTEX_INITIALIZER;

SetNetWork::SetNetWork()
{

}

SetNetWork::~SetNetWork()
{

}

bool SetNetWork::SetIp ( std::string ip, std::string mask )
{
  #if defined(__i386__) || defined(__x86_64__)
  return true;
  #endif
  std::string rcs;

  ReadRcs ( "SYS_IP", rcs );

  if ( rcs != ip )
  {
    ModifyRcs ( "SYS_IP", ip );
    XmlConfig::SetParam ( "IpConfig", "SYS_IP", ip );
  }

  ReadRcs ( "SYS_MASK", rcs );

  if ( rcs != mask )
  {
    ModifyRcs ( "SYS_MASK", mask );
    XmlConfig::SetParam ( "IpConfig", "SYS_MASK", mask );
  }

  return true;
}

bool SetNetWork::SetMac ( std::string mac )
{
  #if defined(__i386__) || defined(__x86_64__)
  return true;
  #endif
  std::string rcs;
  ReadRcs ( "SYS_MAC", rcs );

  if ( rcs != mac )
  {
    ModifyRcs ( "SYS_MAC", mac );
    XmlConfig::SetParam ( "IpConfig", "SYS_MAC", mac );
  }

  return true;
}

bool SetNetWork::SetGateWay ( std::string gw )
{
  #if defined(__i386__) || defined(__x86_64__)
  return true;
  #endif
  std::string rcs;
  ReadRcs ( "SYS_GW", rcs );

  if ( rcs != gw )
  {
    ModifyRcs ( "SYS_GW", gw );
    XmlConfig::SetParam ( "IpConfig", "SYS_GW", gw );
  }

  return true;
}

bool SetNetWork::ModifyRcs ( std::string key, std::string value, std::string fileRcs )
{
  Locker locker ( &m_Mutex );

  std::string str;
  str = "sed -i \"s/^KEY.*$/KEY=VALUE/\" ";
  str += fileRcs;

  if ( std::string::npos != str.find ( "KEY" ) )
    str.replace ( str.find ( "KEY" ), strlen ( "KEY" ), key );

  if ( std::string::npos != str.find ( "KEY" ) )
    str.replace ( str.find ( "KEY" ), strlen ( "KEY" ), key );

  if ( std::string::npos != str.find ( "VALUE" ) )
    str.replace ( str.find ( "VALUE" ), strlen ( "VALUE" ), value );

  system ( str.c_str() );

  return true;
}

bool SetNetWork::ReadRcs ( std::string key, std::string& value, std::string fileRcs )
{
  Locker locker ( &m_Mutex );

  char buffer[32] = "";
  std::string str = "cat FILENAME | grep KEY= | cut -d \"=\" -f2";

  if ( std::string::npos != str.find ( "FILENAME" ) )
    str.replace ( str.find ( "FILENAME" ), strlen ( "FILENAME" ), fileRcs );

  if ( std::string::npos != str.find ( "KEY" ) )
    str.replace ( str.find ( "KEY" ), strlen ( "KEY" ), key );

  FILE* fp = popen ( str.c_str(), "r" );

  if ( !fp )
    return false;

  memset ( buffer, 0, 32 );
  fgets ( buffer, 32, fp );
  pclose ( fp );

  //value  = buffer;
  value.assign ( buffer );

  return true;
}


