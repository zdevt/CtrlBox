/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetWpc.h
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

#ifndef  NETCMDSETWPC_INC
#define  NETCMDSETWPC_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef union
{
  struct
  {
    uint8_t byte0;
    uint8_t byte1;
    uint8_t byte2;
    uint8_t byte3;
  };
  uint32_t iValue;
  float fValue;
} MCP_IEEE754FLOAT_t;

typedef struct
{
  MCP_IEEE754FLOAT_t x;
  MCP_IEEE754FLOAT_t y;
  MCP_IEEE754FLOAT_t Y;
} MCP_xyY_t;

typedef struct
{
  uint8_t mode; 		/*  0~2 0xb4 */
  MCP_xyY_t target; /*  0xb2  */
} set_wpc_t;
#pragma pack(pop)

class NetCmdSetWpc : public NetCmd
{
  public:
    NetCmdSetWpc ( );
    virtual ~NetCmdSetWpc();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

