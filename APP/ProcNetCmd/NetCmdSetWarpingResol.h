/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetWarpingResol.h
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

#ifndef  NETCMDSETWARPINGRESOL_INC
#define  NETCMDSETWARPINGRESOL_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t width;
  uint32_t height;
} set_warpingresol_t;
#pragma pack(pop)

class NetCmdSetWarpingResol : public NetCmd
{
  public:
    NetCmdSetWarpingResol ( );
    virtual ~NetCmdSetWarpingResol();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

