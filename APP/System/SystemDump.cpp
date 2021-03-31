/*
 * =====================================================================================
 *
 *       Filename:  SystemDump.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月07日 10时19分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <execinfo.h>
#include <signal.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "SystemDump.h"

unsigned long getFileSize ( const char* path )
{
  unsigned long filesize = -1;
  struct stat statbuff;

  if ( stat ( path, &statbuff ) < 0 )
  {
    return filesize;
  }
  else
  {
    filesize = statbuff.st_size;
  }

  return filesize;
}

int cutFile ( const char* srcFile, const char* dstFile )
{
  if ( !srcFile || !dstFile )
  {
    return -1;
  }

  int len = 0;
  char buff[1024];

  int fd  = open ( srcFile, O_RDWR | O_CREAT );

  if ( fd <= 0 )
  {
    return -2;
  }

  remove ( dstFile );
  int fd2 = open ( dstFile, O_RDWR | O_CREAT );

  if ( fd2 <= 0 )
  {
    close ( fd );
    return -3;
  }

  while ( ( len = read ( fd, buff, 1024 ) ) > 0 )
  {
    write ( fd2, buff, len );
  }

  close ( fd );
  close ( fd2 );

  remove ( srcFile );

  return 0;
}


SystemDump::SystemDump()
{

}

SystemDump::~SystemDump()
{

}

/**
 * @brief 处理中断函数，纪录信息，返回到原上下文位置，然后中断继续产生。
 *        这样会导致一个终端会循环多次进入这个函数，同样的信息会被保存多次。
 */
void SystemDump::Dump ( int signo )
{
  if ( getFileSize ( DUMP_FILE_NAME ) >= MAX_DUMP_FILE_SIZE )
  {
    cutFile ( DUMP_FILE_NAME, DUMPBAK_FILE_NAME );
  }

  const int vecpvoidSize = 256;
  std::vector<void*> vecpvoid;
  vecpvoid.clear();
  vecpvoid.resize ( vecpvoidSize, NULL );

  const int timeBufferSize = 256;
  char timeBufer[timeBufferSize];

  std::ofstream ofs;
  ofs.open ( DUMP_FILE_NAME, std::ofstream::binary | std::ofstream::app );

  size_t size = 0;
  size = backtrace ( &vecpvoid[0], vecpvoid.size() );

  char** strings = NULL;
  strings = backtrace_symbols ( &vecpvoid[0], size );

  time_t timeNow = time ( NULL );
  std::stringstream ss;
  memset ( timeBufer, 0, timeBufferSize );
  std::string timeStr = ctime_r ( &timeNow, timeBufer );
  ss << signo << " " << timeStr;

  ofs << ss.str();

  for ( uint32_t i = 0; i < size; ++i )
    ofs << i << " " << strings[i] << "\n";

  ofs << "\n";

  ofs.close();

  free ( strings );
  strings = NULL;

  #if !defined(__i386__) && !defined(__x86_64__)
  //system ( "reboot" );
  #endif

  //exit ( 0 );
}

void SystemDump::CatchDump()
{
  setpgrp();
  signal ( SIGSEGV, & ( SystemDump::Dump ) );
  signal ( SIGFPE, & ( SystemDump::Dump ) );
}


#ifdef TEST
typedef struct
{
  int a;
  int b;
} test_t;

void test()
{
  test_t* a = NULL;
  a->a = 1;
  a->b = 2;
}

int main ( int argc, char* argv[] )
{
  SystemDump::CatchDump();

  while ( 1 )
  {
    test();
    sleep ( 1 );
  }

  return 0;
}
#endif

