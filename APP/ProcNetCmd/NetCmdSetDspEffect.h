/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDspEffect.h
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

#ifndef  NETCMDSETDSPEFFECT_INC
#define  NETCMDSETDSPEFFECT_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t dspEffect;
} set_dspeffect_t;
#pragma pack(pop)

class NetCmdSetDspEffect : public NetCmd
{
  public:
    NetCmdSetDspEffect ( );
    virtual ~NetCmdSetDspEffect();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

