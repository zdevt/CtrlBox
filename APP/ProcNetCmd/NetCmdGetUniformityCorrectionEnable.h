/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetUniformityCorrectionEnable.h
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
#ifndef  NETCMDGETUNIFORMITYCORRECTIONENABLE_INC
#define  NETCMDGETUNIFORMITYCORRECTIONENABLE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t enable;
} get_ucenable_t;
#pragma pack(pop)

class NetCmdGetUniformityCorrectionEnable: public NetCmd
{
  public:
    NetCmdGetUniformityCorrectionEnable ( );
    virtual ~NetCmdGetUniformityCorrectionEnable ( );

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NetCmdGetUniformityCorrectionEnable.h ----- */

