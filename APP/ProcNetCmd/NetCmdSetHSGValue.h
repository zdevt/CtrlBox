/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetHSGValue.h
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

#ifndef  NETCMDSETHSGVALUE_INC
#define  NETCMDSETHSGVALUE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef union
{
  struct
  {
    uint16_t F: 14;
    uint16_t I: 1;
    uint16_t S: 1;
  };
  uint16_t value;
} MCP_HSGFLOAT_t;

typedef struct
{
  MCP_HSGFLOAT_t redG;
  MCP_HSGFLOAT_t redS;
  MCP_HSGFLOAT_t redH;
  MCP_HSGFLOAT_t greenG;
  MCP_HSGFLOAT_t greenS;
  MCP_HSGFLOAT_t greenH;
  MCP_HSGFLOAT_t blueG;
  MCP_HSGFLOAT_t blueS;
  MCP_HSGFLOAT_t blueH;
  MCP_HSGFLOAT_t cyanG;
  MCP_HSGFLOAT_t cyanS;
  MCP_HSGFLOAT_t cyanH;
  MCP_HSGFLOAT_t magentaG;
  MCP_HSGFLOAT_t magentaS;
  MCP_HSGFLOAT_t magentaH;
  MCP_HSGFLOAT_t yellowG;
  MCP_HSGFLOAT_t yellowS;
  MCP_HSGFLOAT_t yellowH;
  MCP_HSGFLOAT_t whiteG;
  MCP_HSGFLOAT_t whiteS;
  MCP_HSGFLOAT_t whiteH;
} MCP_HSGVALUE_t;

typedef struct
{
  MCP_HSGVALUE_t value;
} set_hsg_value_t;
#pragma pack(pop)

class NetCmdSetHSGValue : public NetCmd
{
  public:
    NetCmdSetHSGValue ( );
    virtual ~NetCmdSetHSGValue();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

