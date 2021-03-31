/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetWarpingCoor.h
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

#ifndef  NETCMDGETWARPINGCOOR_INC
#define  NETCMDGETWARPINGCOOR_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)

#pragma pack(pop)

class NetCmdGetWarpingCoor : public NetCmd
{
  public:
    NetCmdGetWarpingCoor ( );
    virtual ~NetCmdGetWarpingCoor();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

