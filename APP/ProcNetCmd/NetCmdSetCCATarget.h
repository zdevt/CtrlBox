/* * =====================================================================================
 *
 *       Filename:  NetCmdSetCCATarget.h
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

#ifndef  NETCMDSETCCATARGET_INC
#define  NETCMDSETCCATARGET_INC

#include "NetCmd.h"
#include "NetCmdSetWpc.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  MCP_xyY_t red;
  MCP_xyY_t green;
  MCP_xyY_t blue;
  MCP_xyY_t cyan;
  MCP_xyY_t magenta;
  MCP_xyY_t yellow;
} MCP_CCATARGET_t;
typedef struct
{
  uint8_t colorIndex;
  MCP_CCATARGET_t value;
} set_cca_target_t;
#pragma pack(pop)

class NetCmdSetCCATarget : public NetCmd
{
  public:
    NetCmdSetCCATarget ( );
    virtual ~NetCmdSetCCATarget();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

