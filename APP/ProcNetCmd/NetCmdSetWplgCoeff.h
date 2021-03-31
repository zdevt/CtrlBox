/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetWplgCoeff.h
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

#ifndef  NETCMDSETWPLGCOEFF_INC
#define  NETCMDSETWPLGCOEFF_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t wplg[9];
} set_wplgcoeff_t;
#pragma pack(pop)

class NetCmdSetWplgCoeff : public NetCmd
{
  public:
    NetCmdSetWplgCoeff ( );
    virtual ~NetCmdSetWplgCoeff();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

