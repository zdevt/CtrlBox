/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetLutCoeff.h
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

#ifndef  NETCMDSETLUTCOEFF_INC
#define  NETCMDSETLUTCOEFF_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t hlut[24];
  uint8_t vlut[24];
} set_lutcoeff_t;
#pragma pack(pop)

class NetCmdSetLutCoeff : public NetCmd
{
  public:
    NetCmdSetLutCoeff ( );
    virtual ~NetCmdSetLutCoeff();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

