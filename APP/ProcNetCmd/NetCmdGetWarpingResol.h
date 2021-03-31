/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetWarpingResol.h
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

#ifndef  NETCMDGETWARPINGRESOL_INC
#define  NETCMDGETWARPINGRESOL_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t width;
  uint32_t height;
} get_warpingresol_t;
#pragma pack(pop)

class NetCmdGetWarpingResol : public NetCmd
{
  public:
    NetCmdGetWarpingResol ( );
    virtual ~NetCmdGetWarpingResol();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

