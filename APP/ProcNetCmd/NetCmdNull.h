/*
 * =====================================================================================
 *
 *       Filename:  NetCmdNull.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/06/2015 03:13:32 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  NETCMNULL_INC
#define  NETCMNULL_INC

#include "NetCmd.h"

class NetCmdNull : public NetCmd
{
  public:
    NetCmdNull ( );
    virtual ~NetCmdNull();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );
    static std::shared_ptr<NetCmd> GetObj ( );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

