/*
 * =====================================================================================
 *
 *       Filename:  IoDevInterface.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/08/2015 01:12:38 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  IODEVINTERFACE_INC
#define  IODEVINTERFACE_INC

#include <pthread.h>
#include <sstream>
#include <errno.h>
#include <string.h>

class IoDevInterface
{
  private:
    IoDevInterface ( );
    ~IoDevInterface();

  public:
    static int Ioctl ( std::string devname, unsigned int cmd, unsigned long arg );
};

#endif   /* ----- #ifndef IODEV_INC  ----- */

