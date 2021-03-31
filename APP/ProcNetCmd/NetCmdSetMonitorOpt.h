/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetMonitorOpt.h
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

#ifndef  NETCMDSETMONITOROPT_INC
#define  NETCMDSETMONITOROPT_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t monitorOpt;
} set_monitor_opt_t;
#pragma pack(pop)

class NetCmdSetMonitorOpt : public NetCmd
{
  public:
    NetCmdSetMonitorOpt (  );
    virtual ~NetCmdSetMonitorOpt();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

