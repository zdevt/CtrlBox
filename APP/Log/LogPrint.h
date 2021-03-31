/*
 * =====================================================================================
 *
 *       Filename:  LogPrint.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月07日 17时04分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  LOGPRINT_INC
#define  LOGPRINT_INC

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>

#define LOG_DISP_TERM     "/dev/pts/0"
#define LOG_BLACK         "\033[30m_LOGSTRING_\033[0m"
#define LOG_RED           "\033[1;31m_LOGSTRING_\033[0m"

#define _LOG_BLACK       "\033[m_LOGSTRING_\033[0m"
#define _LOG_RED         "\033[0;32;31m_LOGSTRING_\033[0m"
#define LOG_LIGHT_RED    "\033[1;31m_LOGSTRING_\033[0m"
#define LOG_GREEN        "\033[0;32;32m_LOGSTRING_\033[0m"
#define LOG_LIGHT_GREEN  "\033[1;32m_LOGSTRING_\033[0m"
#define LOG_BLUE         "\033[0;32;34m_LOGSTRING_\033[0m"
#define LOG_LIGHT_BLUE   "\033[1;34m_LOGSTRING_\033[0m"
#define LOG_DARY_GRAY    "\033[1;30m_LOGSTRING_\033[0m"
#define LOG_CYAN         "\033[0;36m_LOGSTRING_\033[0m"
#define LOG_LIGHT_CYAN   "\033[1;36m_LOGSTRING_\033[0m"
#define LOG_PURPLE       "\033[0;35m_LOGSTRING_\033[0m"
#define LOG_LIGHT_PURPLE "\033[1;35m_LOGSTRING_\033[0m"
#define LOG_BROWN        "\033[0;33m_LOGSTRING_\033[0m"
#define LOG_YELLOW       "\033[1;33m_LOGSTRING_\033[0m"
#define LOG_LIGHT_GRAY   "\033[0;37m_LOGSTRING_\033[0m"
#define LOG_WHITE        "\033[1;37m_LOGSTRING_\033[0m"

#define PRINT_LOG( level, fmt, arg...)  LogPrint::Print( level, __FILE__, __LINE__,__FUNCTION__,fmt,##arg)
#define PRINT_LOG2( fmt, arg...)        LogPrint::Print2( fmt,##arg)

#if !defined(__i386__) && !defined(__x86_64__)
  #define LOG_FILE_NAME "/app/log.txt"
#else
  #define LOG_FILE_NAME "log.txt"
#endif

enum
{
  LOG_LEVEL_NORMAL = 0,
  LOG_LEVEL_INFO,
  LOG_LEVEL_ALARM,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL, /* save log to file */

  LOG_LEVEL_MAX,
};

#define MAX_STR_BUFFER    (2014)

class LogPrint
{
  private:
    LogPrint();
    ~LogPrint();

  public:
    static int Print ( uint32_t level, const char* filename,
                       int fileline, const char* function, const char* fmt, ... );

    static int Print2 ( const char* fmt, ... );
  private:
    static int WriteToFile ( std::string s );
    static int WriteToTerm ( const char* msg, int len );
    static int WriteToStd ( const char* msg, int len );

};


#endif   /* ----- #ifndef LogPrint.h ----- */

