/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDmdGamma.h
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

#ifndef  NETCMDSETDMDGAMMA_INC
#define  NETCMDSETDMDGAMMA_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t gammaType;
} set_dmd_gamma_t;
#pragma pack(pop)

class NetCmdSetDmdGamma : public NetCmd
{
  public:
    NetCmdSetDmdGamma ( );
    virtual ~NetCmdSetDmdGamma();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

