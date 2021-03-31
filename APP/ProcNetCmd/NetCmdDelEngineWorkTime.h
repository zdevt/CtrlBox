/*
 * =====================================================================================
 *
 *       Filename:  NetCmdDelEngineWorkTime.h
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

#ifndef  NETCMDDELENGINEWORKTIME_INC
#define  NETCMDDELENGINEWORKTIME_INC

#include "NetCmd.h"

class NetCmdDelEngineWorkTime : public NetCmd
{
  public:
    NetCmdDelEngineWorkTime ( );
    virtual ~NetCmdDelEngineWorkTime();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

