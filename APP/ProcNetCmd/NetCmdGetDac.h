/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetDac.h
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

#ifndef  NETCMDGETDAC_INC
#define  NETCMDGETDAC_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef union
{
  struct
  {
    /*  bit0: red; bit1: green; bit2: blue */
    uint8_t red: 1;
    uint8_t green: 1;
    uint8_t blue: 1;
    uint8_t : 5;
  };
  uint16_t mask;
} get_dac_mask_t;

typedef struct
{
  uint16_t basic; /*0:当前， 1:实际 */
  get_dac_mask_t get_dac_mask;
} get_dac_cmd_t;

typedef struct
{
  uint16_t red;
  uint16_t green;
  uint16_t blue;
} get_component_dac_value_t;

typedef struct
{
  get_dac_mask_t mask;
  get_component_dac_value_t red;
  get_component_dac_value_t green;
  get_component_dac_value_t blue;
} get_dac_t;
#pragma pack(pop)

class NetCmdGetDac : public NetCmd
{
  public:
    NetCmdGetDac ( );
    virtual ~NetCmdGetDac();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

