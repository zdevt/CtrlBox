/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetWarpingOnlineState.h
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

#ifndef  NETCMDGETWARPINGONLINESTATE_INC
#define  NETCMDGETWARPINGONLINESTATE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t online; /*  0不在线,1在线 */
} get_warpingonlinestate_t;
#pragma pack(pop)

class NetCmdGetWarpingOnlineState : public NetCmd
{
  public:
    NetCmdGetWarpingOnlineState ( );
    virtual ~NetCmdGetWarpingOnlineState();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

