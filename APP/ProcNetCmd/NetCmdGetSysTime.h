/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetSysTime.h
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

#ifndef  NETCMDGETSYSTIME_INC
#define  NETCMDGETSYSTIME_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint16_t year;
  uint16_t month;
  uint16_t day;
  uint16_t hour;
  uint16_t minute;
  uint16_t second;
} get_systime_t;
#pragma pack(pop)

class NetCmdGetSysTime : public NetCmd
{
  public:
    NetCmdGetSysTime ( );
    virtual ~NetCmdGetSysTime();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

