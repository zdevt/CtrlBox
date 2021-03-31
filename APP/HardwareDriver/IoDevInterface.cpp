/*
 * =====================================================================================
 *
 *       Filename:  IoDevInterface.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/08/2015 01:12:32 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "IoDevInterface.h"


IoDevInterface::IoDevInterface ( )
{

}

IoDevInterface::~IoDevInterface()
{

}

int IoDevInterface::Ioctl ( std::string devname, unsigned int cmd, unsigned long arg )
{
  int ret = -1;
  int devfd = open ( devname.c_str(), O_RDWR );

  if ( devfd < 0 )
    return ret;

  ret = ioctl ( devfd, cmd, arg ); /* return a nonnegative value on success.*/

  close ( devfd );

  return ret;
}

