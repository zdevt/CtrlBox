/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetPowerState.h
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

#ifndef  NETCMDGETPOWERSTATE_INC
#define  NETCMDGETPOWERSTATE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t name[MCP_NAME_LEN];
  uint32_t voltage; /*  *100  */
  uint32_t ampere;
  uint32_t watt;
  int32_t celsius;
  uint32_t status;
} MCP_POWER_t;

typedef struct
{
  uint32_t uiPowerNum;
  MCP_POWER_t powerState[0];
} get_powerstate_t;
#pragma pack(pop)

class NetCmdGetPowerState : public NetCmd
{
  public:
    NetCmdGetPowerState ( );
    virtual ~NetCmdGetPowerState();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

