/*
 * =====================================================================================
 *
 *       Filename:  SystemDump.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月07日 10时19分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  SYSTEMDUMP_INC
#define  SYSTEMDUMP_INC

#if !defined(__i386__) && !defined(__x86_64__)
  #define DUMP_FILE_NAME        "/app/dump.txt"
  #define DUMPBAK_FILE_NAME     "/app/dump_bak.txt"
#else
  #define DUMP_FILE_NAME        "dump.txt"
  #define DUMPBAK_FILE_NAME     "dump_bak.txt"
#endif

#define MAX_DUMP_FILE_SIZE    (0x200000)

class SystemDump
{
  private:
    SystemDump();
    ~SystemDump();

  public:
    static void Dump ( int signal );
    static void CatchDump();

};


#endif   /* ----- #ifndef SystemDump.h ----- */

