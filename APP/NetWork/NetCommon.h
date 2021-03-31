/*
 * =====================================================================================
 *
 *       Filename:  NetCommon.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年03月27日 23时12分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  NETCOMMON_INC
#define  NETCOMMON_INC

#include <string>
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>
#include <ifaddrs.h>

typedef std::vector<std::string> vecstr_t;

class NetCommon
{
  private:
    NetCommon();
    ~NetCommon();

  public:
    static bool GetAllLocalIp ( vecstr_t& vecstr );
    static bool IsLocalIp ( std::string ip );
};


#endif   /* ----- #ifndef NetCommon.h ----- */

