/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetWarpingCoor.h
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

#ifndef  NETCMDSETWARPINGCOOR_INC
#define  NETCMDSETWARPINGCOOR_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint16_t x;   /*  最高位表示符号，最低4位表示小数，其他表示整数 */
  uint16_t y;   /*  最高位表示符号，最低4位表示小数，其他表示整数 */
} MCP_POINT_T;

typedef struct
{
  MCP_POINT_T lefttop;
  MCP_POINT_T leftrighttop;
  MCP_POINT_T top;
  MCP_POINT_T rightlefttop;
  MCP_POINT_T righttop;

  MCP_POINT_T topright;
  MCP_POINT_T right;
  MCP_POINT_T downright;

  MCP_POINT_T rightdown;
  MCP_POINT_T rightleftdown;
  MCP_POINT_T down;
  MCP_POINT_T leftrightdown;
  MCP_POINT_T leftdown;

  MCP_POINT_T downleft;
  MCP_POINT_T left;
  MCP_POINT_T topleft;
} MCP_WARPINGCOOR_T;

#pragma pack(pop)

class NetCmdSetWarpingCoor : public NetCmd
{
  public:
    NetCmdSetWarpingCoor ( );
    virtual ~NetCmdSetWarpingCoor();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

