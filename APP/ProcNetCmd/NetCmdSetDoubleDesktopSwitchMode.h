/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDoubleDesktopSwitchMode.h
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

#ifndef  NETCMDSETDOUBLEDESKTOPSWITCHMODE_INC
#define  NETCMDSETDOUBLEDESKTOPSWITCHMODE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t mode; /*  0 自动， 1手动 */
} set_mode_t;
#pragma pack(pop)

class NetCmdSetDoubleDesktopSwitchMode : public NetCmd
{
  public:
    NetCmdSetDoubleDesktopSwitchMode ( );
    virtual ~NetCmdSetDoubleDesktopSwitchMode();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

