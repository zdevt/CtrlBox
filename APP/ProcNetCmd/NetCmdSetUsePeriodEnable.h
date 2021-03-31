/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetUsePeriodEnable.h
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

#ifndef  NETCMDSETUSERPERIODENABLE_INC
#define  NETCMDSETUSERPERIODENABLE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t enable; /*  0：非使能， 1：使能  */
} set_use_period_enable_t;
#pragma pack(pop)

class NetCmdSetUsePeriodEnable : public NetCmd
{
  public:
    NetCmdSetUsePeriodEnable ( );
    virtual ~NetCmdSetUsePeriodEnable();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

