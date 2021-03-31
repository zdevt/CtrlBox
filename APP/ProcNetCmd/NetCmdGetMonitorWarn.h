/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetMonitorWarn.h
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

#ifndef  NETCMDGETMONITORWARN_INC
#define  NETCMDGETMONITORWARN_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t monitorOpt;
} get_monitor_warn_cmd_t;

typedef struct
{
  uint32_t monitorOpt;
  int minValue;
  int maxValue;
} get_monitor_warn_t;
#pragma pack(pop)

class NetCmdGetMonitorWarn : public NetCmd
{
  public:
    NetCmdGetMonitorWarn (  );
    virtual ~NetCmdGetMonitorWarn();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

