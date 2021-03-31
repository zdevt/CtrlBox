/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetBcMode.h
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

#ifndef  NETCMDGETBCMODE_INC
#define  NETCMDGETBCMODE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t bcMode;
} get_bcmode_t;
#pragma pack(pop)

class NetCmdGetBcMode : public NetCmd
{
  public:
    NetCmdGetBcMode ( );
    virtual ~NetCmdGetBcMode();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

