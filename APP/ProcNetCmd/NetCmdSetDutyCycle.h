/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDutyCycle.h
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

#ifndef  NETCMDSETDUTYCYCLE_INC
#define  NETCMDSETDUTYCYCLE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t dcIndex;
} set_dc_index_t;
#pragma pack(pop)

class NetCmdSetDutyCycle : public NetCmd
{
  public:
    NetCmdSetDutyCycle ( );
    virtual ~NetCmdSetDutyCycle();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

