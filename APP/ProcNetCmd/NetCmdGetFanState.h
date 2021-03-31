/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetFanState.h
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

#ifndef  NETCMDGETFANSTATE_INC
#define  NETCMDGETFANSTATE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t name[MCP_NAME_LEN];
  uint32_t rate;
  uint32_t status; /*  0:ok ; 1:error */
} MCP_FAN_t;

typedef struct
{
  uint32_t uiFanType;
} get_fanstate_cmd_t;

typedef struct
{
  uint32_t uiFanNum;
  MCP_FAN_t fanstate[0];
} get_fanstate_t;
#pragma pack(pop)

class NetCmdGetFanState : public NetCmd
{
  public:
    NetCmdGetFanState ( );
    virtual ~NetCmdGetFanState();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

