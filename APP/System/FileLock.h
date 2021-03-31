/*
 * =====================================================================================
 *
 *       Filename:  FileLock.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/23/2015 09:14:49 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  FILELOCK_INC
#define  FILELOCK_INC

#include <string>

#define DEFAULT_FILELOCK_NAME   ("/app/lock")

class FileLock
{
  private:
    FileLock();
    ~FileLock();

  public:
    static bool GetLock ( std::string filename = DEFAULT_FILELOCK_NAME );
};


#endif   /* ----- #ifndef FILELOCK_INC  ----- */

