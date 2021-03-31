/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetCubewallConf.h
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

#ifndef  NETCMDGETCUBEWALLCONF_INC
#define  NETCMDGETCUBEWALLCONF_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t id;
  uint16_t wallRows;
  uint16_t wallCols;
  uint16_t cubeID;
} get_cubewall_conf_t;
#pragma pack(pop)

class NetCmdGetCubewallConf : public NetCmd
{
  public:
    NetCmdGetCubewallConf ( );
    virtual ~NetCmdGetCubewallConf();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

