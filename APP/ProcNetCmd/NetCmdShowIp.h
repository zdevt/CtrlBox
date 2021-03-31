/*
 * =====================================================================================
 *
 *       Filename:  NetCmdShowIp.h
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

#ifndef  NETCMDSHOWIP_INC
#define  NETCMDSHOWIP_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t flag;
  uint8_t range;
} show_ip_t;
#pragma pack(pop)

class NetCmdShowIp : public NetCmd
{
  public:
    NetCmdShowIp (  );
    virtual ~NetCmdShowIp();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

