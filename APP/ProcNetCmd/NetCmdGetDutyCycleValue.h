/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetDutyCycleValue.h
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

#ifndef  NETCMDGETDUTYCYCLEVALUE_INC
#define  NETCMDGETDUTYCYCLEVALUE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  unsigned char	lsb;
  unsigned char	msb;
} MCP_DC_LSBAndMSB_t;

typedef struct
{
  MCP_DC_LSBAndMSB_t 	desiredRed;
  MCP_DC_LSBAndMSB_t 	desiredGreen;
  MCP_DC_LSBAndMSB_t 	desiredBlue;
  MCP_DC_LSBAndMSB_t 	actualRed;
  MCP_DC_LSBAndMSB_t 	actualGreen;
  MCP_DC_LSBAndMSB_t 	actualBlue;
  MCP_DC_LSBAndMSB_t 	actualCyan;
  MCP_DC_LSBAndMSB_t 	actualMagenta;
  MCP_DC_LSBAndMSB_t 	actualYellow;
  MCP_DC_LSBAndMSB_t 	actualWhite;
} get_dc_value_t;
#pragma pack(pop)

class NetCmdGetDutyCycleValue : public NetCmd
{
  public:
    NetCmdGetDutyCycleValue ( );
    virtual ~NetCmdGetDutyCycleValue();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

