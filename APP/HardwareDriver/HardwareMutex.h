/*
 * =====================================================================================
 *
 *       Filename:  HardwareMutex.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/10/2015 08:18:15 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  HARDWAREMUTEX_INC
#define  HARDWAREMUTEX_INC

#include <map>
#include <string>

typedef std::map<std::string, pthread_mutex_t> mapIoDevMutex_t;

class HardwareMutex
{
  private:
    HardwareMutex();
    ~HardwareMutex();

  public:
    static pthread_mutex_t* GetMutex ( std::string devname );

  public:
    static mapIoDevMutex_t m_mapIoDevMutex;
};

#endif   /* ----- #ifndef HAREWAREMUTEXADMIN_INC  ----- */

