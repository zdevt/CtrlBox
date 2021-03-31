/*
 * =====================================================================================
 *
 *       Filename:  GetNetWork.h
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
#ifndef  GETNETWORK_INC
#define  GETNETWORK_INC

#include <string>

class GetNetWork
{
  private:
    explicit GetNetWork();
    virtual ~GetNetWork();

  public:
    static bool GetIp ( std::string& ip, std::string& mask );
    static bool GetMac ( std::string& mac );
    static bool GetGateWay ( std::string& gw );
};

#endif   /* ----- #ifndef GetNetWork.h ----- */

