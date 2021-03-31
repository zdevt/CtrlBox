/*
 * =====================================================================================
 *
 *       Filename:  WatchDogDev.h
 *
 *
 *   Description:
 *
 *
 *        Version:  1.0
 *        Created:  01/11/2015 09:31:18 PM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  WATCHDOGDEV_INC
#define  WATCHDOGDEV_INC


class WatchDogDev
{
  public:
    WatchDogDev ( );
    virtual ~WatchDogDev();

  public:
    virtual int Feed() = 0;
    virtual int Enable() = 0;
    virtual int Disable() = 0;

};


#endif   /* ----- #ifndef WATCHDOGDEV_INC  ----- */

