/*
 * =====================================================================================
 *
 *       Filename:  FileLock.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/23/2015 09:14:43 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <fcntl.h>
#include <unistd.h>

#include "FileLock.h"

FileLock::FileLock()
{
}

FileLock::~FileLock()
{
}

bool FileLock::GetLock ( std::string filename )
{
  int fd = -1;
  int ret = -1;

  fd = open ( filename.c_str(), O_RDWR );

  if ( fd < 0 )
    return false;

  ret = lockf ( fd, F_TEST, 0 );

  if ( ret < 0 )
  {
    close ( fd );
    return false;
  }

  ret = lockf ( fd, F_LOCK, 0 );

  if ( ret < 0 )
  {
    close ( fd );
    return false;
  }

  return true;
}



#ifdef TEST

int main ( int argc, char* argv[] )
{

  FileLock::GetLock ( "/tmp/a.lock" );

  return 0;
}

#endif
