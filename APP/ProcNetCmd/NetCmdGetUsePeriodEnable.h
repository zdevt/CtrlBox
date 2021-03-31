/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetUsePeriodEnable.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07/31/2017 10:10:49 AM
 *  Last Modified:  07/31/2017 10:10:49 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  NETCMDGETUSEPERIODENABLE_INC
#define  NETCMDGETUSEPERIODENABLE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t enable; /*  0：非使能， 1：使能  */
} get_useperiod_enable_t;
#pragma pack(pop)

class NetCmdGetUsePeriodEnable : public NetCmd
{
  public:
    NetCmdGetUsePeriodEnable( );
    virtual ~NetCmdGetUsePeriodEnable();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NetCmdGetUsePeriodEnable.h ----- */

