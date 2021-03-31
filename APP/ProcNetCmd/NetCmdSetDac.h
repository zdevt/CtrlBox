/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDac.h
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

#ifndef  NETCMDSETDAC_INC
#define  NETCMDSETDAC_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef union
{
  struct
  {
    uint8_t red: 1;
    uint8_t green: 1;
    uint8_t blue: 1;
    uint8_t : 5;
  };
  uint16_t mask;
} set_dac_mask_t;

typedef struct
{
  uint16_t red;
  uint16_t green;
  uint16_t blue;
} component_dac_value_t;

typedef struct
{
  uint16_t basic; /*  0:当前 1: 基准 */
  set_dac_mask_t mask;
  component_dac_value_t red;
  component_dac_value_t green;
  component_dac_value_t blue;
} set_dac_t;
#pragma pack(pop)

class NetCmdSetDac : public NetCmd
{
  public:
    NetCmdSetDac ( );
    virtual ~NetCmdSetDac();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

