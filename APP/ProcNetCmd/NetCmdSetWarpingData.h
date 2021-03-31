/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetWarpingData.h
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

#ifndef  NETCMDSETWARPINGDATA_INC
#define  NETCMDSETWARPINGDATA_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t grid;
  uint32_t datalen;
  uint8_t data[0];
} set_warpingdata_t;
#pragma pack(pop)

class NetCmdSetWarpingData : public NetCmd
{
  public:
    NetCmdSetWarpingData ( );
    virtual ~NetCmdSetWarpingData();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

