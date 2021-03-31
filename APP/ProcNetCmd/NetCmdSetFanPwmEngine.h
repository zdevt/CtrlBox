/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetFanPwmEngine.h
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

#ifndef  NETCMDSETFANPWMENGINE_INC
#define  NETCMDSETFANPWMENGINE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t fan_id;
  uint8_t fan_pwm;
} set_fan_pwm_t;
#pragma pack(pop)

class NetCmdSetFanPwmEngine : public NetCmd
{
  public:
    NetCmdSetFanPwmEngine ( );
    virtual ~NetCmdSetFanPwmEngine();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDSETFANPWMENGINE_INC----- */

