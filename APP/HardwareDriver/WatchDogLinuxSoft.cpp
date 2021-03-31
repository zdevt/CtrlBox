/*
 * =====================================================================================
 *
 *       Filename:  WatchDogLinuxSoft.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/11/2015 09:31:00 PM EST
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
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/watchdog.h>
#include <string.h>

#include "WatchDogLinuxSoft.h"


WatchDogLinuxSoft::WatchDogLinuxSoft ( )
{
  m_fd = open ( "/dev/watchdog", O_WRONLY );
}


WatchDogLinuxSoft::~WatchDogLinuxSoft()
{
  if ( m_fd > 0 )
    close ( m_fd );
}

WatchDogLinuxSoft* WatchDogLinuxSoft::GetInstance()
{
  static WatchDogLinuxSoft instance;
  return &instance;
}

void WatchDogLinuxSoft::Feed()
{
  int dummy;

  if ( m_fd > 0 )
    ioctl ( m_fd, WDIOC_KEEPALIVE, &dummy );
}

void WatchDogLinuxSoft::Enable()
{
  if ( m_fd > 0 )
    ioctl ( m_fd, WDIOC_SETOPTIONS, WDIOS_ENABLECARD );
}

void WatchDogLinuxSoft::Disable()
{
  if ( m_fd > 0 )
    ioctl ( m_fd, WDIOC_SETOPTIONS, WDIOS_DISABLECARD );
}

void WatchDogLinuxSoft::SetTimeOut ( int s )
{
  int timeout = s;

  if ( m_fd > 0 )
    ioctl ( m_fd, WDIOC_SETTIMEOUT, &timeout );
}

void WatchDogLinuxSoft::GetTimeOut ( int& s )
{
  if ( m_fd > 0 )
    ioctl ( m_fd, WDIOC_GETTIMEOUT, &s );
}

#ifdef TEST

int main ( int argc, char* argv[] )
{
  int timeout;
  auto p = WatchDogLinuxSoft::GetInstance();

  // p->Enable();
  p->SetTimeOut ( 2 );
  p->GetTimeOut ( timeout );
  fprintf ( stderr, "timeout=%d\n", timeout );
  p->Disable();

  #if 1

  while ( 1 )
  {
    //p->Feed();
    //fprintf ( stderr, "Feed Dog!\n" );
    sleep ( 1 );
  }

  #endif

  return 0;
}

#endif


