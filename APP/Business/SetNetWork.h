/*
 * =====================================================================================
 *
 *       Filename:  SetNetWork.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/11/2015 11:09:39 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  SETNETWORK_INC
#define  SETNETWORK_INC

#include <string>

#define RCS_FILENAME "/etc/init.d/rcS"

#define DEFAULT_MASK "255.255.255.0"

class SetNetWork
{
  private:
    explicit SetNetWork();
    virtual ~SetNetWork();

  public:
    static bool SetIp ( std::string ip, std::string mask = DEFAULT_MASK );
    static bool SetMac ( std::string mac );
    static bool SetGateWay ( std::string gw );

  private:
    static bool ModifyRcs ( std::string key, std::string value, std::string fileRcs = RCS_FILENAME );
    static bool ReadRcs ( std::string key, std::string& value, std::string fileRcs = RCS_FILENAME );

  private:
    static pthread_mutex_t m_Mutex;
};

#endif   /* ----- #ifndef SetNetWork.h ----- */

