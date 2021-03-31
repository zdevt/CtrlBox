/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetNetWork.h
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

#ifndef  NETCMDGETNETWORK_INC
#define  NETCMDGETNETWORK_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t mac[24];
  uint8_t ip[24];
  uint8_t mask[24];
  uint8_t gw[24];
} get_network_t;
#pragma pack(pop)

class NetCmdGetNetWork : public NetCmd
{
  public:
    NetCmdGetNetWork ( );
    virtual ~NetCmdGetNetWork();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

