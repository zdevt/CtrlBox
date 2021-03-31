/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetUniformityCorrectionEnable.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/10/2017 10:38:06 AM
 *  Last Modified:  08/10/2017 10:38:06 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  NETCMDSETUNIFORMITYCORRECTIONENABLE_INC
#define  NETCMDSETUNIFORMITYCORRECTIONENABLE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t enable;
} set_ucenable_t;
#pragma pack(pop)

class NetCmdSetUniformityCorrectionEnable: public NetCmd
{
  public:
    NetCmdSetUniformityCorrectionEnable ( );
    virtual ~NetCmdSetUniformityCorrectionEnable ( );

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NetCmdSetUniformityCorrectionEnable.h ----- */

