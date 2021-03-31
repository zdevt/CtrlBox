/*
 * =====================================================================================
 *
 *       Filename:  WatchDogLinuxSoft.h
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

#ifndef  WATCHDOGLINUXSOFT_INC
#define  WATCHDOGLINUXSOFT_INC


class WatchDogLinuxSoft
{
  private:
    WatchDogLinuxSoft ( );
    ~WatchDogLinuxSoft();

  public:
    static WatchDogLinuxSoft* GetInstance();
    void Feed();
    void Enable();
    void Disable();
    void SetTimeOut ( int s );
    void GetTimeOut ( int& s );

  private:
    int m_fd;
};


#endif   /* ----- #ifndef WATCHDOGDEV_INC  ----- */

