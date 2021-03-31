/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetTargetLuminance.h
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

#ifndef  NETCMDSETBCTARGETLUMINANCE_INC
#define  NETCMDSETBCTARGETLUMINANCE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef union
{
  struct
  {
    uint8_t r: 1;
    uint8_t g: 1;
    uint8_t b: 1;
    uint8_t : 5;
  };
  uint32_t mask;
} set_luminance_cmd_t;

typedef struct
{
  uint32_t r;
  uint32_t g;
  uint32_t b;
} set_luminance_t;

typedef struct
{
  set_luminance_cmd_t cmd;
  set_luminance_t r;
  set_luminance_t g;
  set_luminance_t b;
} set_targetluminance_t;
#pragma pack(pop)

class NetCmdSetTargetLuminance : public NetCmd
{
  public:
    NetCmdSetTargetLuminance ( );
    virtual ~NetCmdSetTargetLuminance();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

