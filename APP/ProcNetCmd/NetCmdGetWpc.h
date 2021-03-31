/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetWpc.h
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

#ifndef  NETCMDGETWPC_INC
#define  NETCMDGETWPC_INC

#include "NetCmd.h"
#include "NetCmdSetWpc.h"

#define get_wpc_t set_wpc_t

#pragma pack(push)
#pragma pack(1)

#pragma pack(pop)

class NetCmdGetWpc : public NetCmd
{
  public:
    NetCmdGetWpc ( );
    virtual ~NetCmdGetWpc();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

