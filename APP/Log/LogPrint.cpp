/*
 * =====================================================================================
 *
 *       Filename:  LogPrint.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月07日 17时04分23秒
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
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sys/syscall.h>
#include <fstream>

#include "LogPrint.h"

LogPrint::LogPrint()
{

}

LogPrint::~LogPrint()
{

}

int LogPrint::WriteToStd ( const char* msg, int len )
{
  int wrLen = 0;
  int haveWr = 0;
  int needToWr = len;

  do
  {
    wrLen = fprintf ( stderr, "%s", msg + haveWr );
    haveWr += wrLen;
    needToWr -= wrLen;
  }
  while ( ( needToWr > 0 ) && ( wrLen > 0 ) );

  return haveWr;
}

int LogPrint::WriteToTerm ( const char* msg, int len )
{
  #if !defined(__i386__) && !defined(__x86_64__)
  int fd = open ( LOG_DISP_TERM, O_WRONLY | O_NOCTTY | O_NDELAY );

  if ( fd < 0 )
    return WriteToStd ( msg, len );

  int wrLen = 0;
  int haveWr = 0;
  int needToWr = len;

  do
  {
    wrLen = write ( fd, msg + haveWr, needToWr );
    haveWr += wrLen;
    needToWr -= wrLen;
  }
  while ( ( needToWr > 0 ) && ( wrLen > 0 ) );

  close ( fd );

  return haveWr;
  #else
  return WriteToStd ( msg, len );
  #endif
}

int LogPrint::Print2 ( const char* fmt, ... )
{
  char strBuffer[MAX_STR_BUFFER];
  va_list arg;

  va_start ( arg, fmt );
  vsnprintf ( strBuffer, MAX_STR_BUFFER, fmt, arg );
  va_end ( arg );

  std::string strIn = strBuffer;

  return WriteToTerm ( strIn.c_str(), strIn.size() );
}

int LogPrint::Print ( uint32_t level, const char* filename,
                      int fileline, const char* function, const char* fmt, ... )
{
  time_t timeNow = time ( NULL );
  tm tmNow;
  localtime_r ( &timeNow, &tmNow );
  int tid = syscall ( SYS_gettid );

  std::stringstream ss;
  ss << tmNow.tm_year + 1900
     << std::setfill ( '0' ) << std::setw ( 2 ) << tmNow.tm_mon + 1
     << std::setfill ( '0' ) << std::setw ( 2 ) << tmNow.tm_mday << " "
     << std::setfill ( '0' ) << std::setw ( 2 ) << tmNow.tm_hour << ":"
     << std::setfill ( '0' ) << std::setw ( 2 ) << tmNow.tm_min << ":"
     << std::setfill ( '0' ) << std::setw ( 2 ) << tmNow.tm_sec << " "
     << std::setw ( 4 ) << tid << " "
     << filename << " " << fileline << " " << function << "] ";

  char strBuffer[MAX_STR_BUFFER];
  va_list arg;

  va_start ( arg, fmt );
  vsnprintf ( strBuffer, MAX_STR_BUFFER, fmt, arg );
  va_end ( arg );

  std::string strOut = ss.str();

  if ( level == LOG_LEVEL_ALARM )
    strOut += LOG_BROWN;
  else if ( level == LOG_LEVEL_ERROR )
    strOut += LOG_YELLOW;
  else if ( level == LOG_LEVEL_FATAL )
    strOut += LOG_RED;
  else
    strOut += LOG_GREEN;

  std::string strIn = strBuffer;

  if ( level >= LOG_LEVEL_FATAL )
    WriteToFile ( ss.str() + strIn );

  strOut.replace ( strOut.find ( "_LOGSTRING_" ), strlen ( "_LOGSTRING_" ), strIn );

  return WriteToTerm ( strOut.c_str(), strOut.size() );
}


int LogPrint::WriteToFile ( std::string s )
{
  std::ofstream ofs ( LOG_FILE_NAME, std::ofstream::binary | std::ofstream::app );

  if ( ofs )
    ofs << s;

  return 0;
}

#ifdef TEST
void TestPrintLog( )
{
  PRINT_LOG ( LOG_LEVEL_FATAL, "%d %s %f\n", 1, "2222", 1.222 );
}

int main ( int argc, char* argv[] )
{
  TestPrintLog( );
  return 0;
}
#endif

