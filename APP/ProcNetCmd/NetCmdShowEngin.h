/*
 * =====================================================================================
 *
 *       Filename:  NetCmdShowEngin.h
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

#ifndef  NETCMDSHOWENGIN_INC
#define  NETCMDSHOWENGIN_INC

#include "NetCmd.h"

class NetCmdShowEngin : public NetCmd
{
  public:
    NetCmdShowEngin ( );
    virtual ~NetCmdShowEngin();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

