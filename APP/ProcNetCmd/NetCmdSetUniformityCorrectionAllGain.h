/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetUniformityCorrectionAllGain.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/10/2017 11:32:07 AM
 *  Last Modified:  08/10/2017 11:32:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  NETCMDSETUNIFORMITYCORRECTIONALLGAIN_INC
#define  NETCMDSETUNIFORMITYCORRECTIONALLGAIN_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t  level;
  uint32_t  gainNum;
  uint16_t  gain[0];
} set_ucallgain_t;
#pragma pack(pop)

class NetCmdSetUniformityCorrectionAllGain: public NetCmd
{
  public:
    NetCmdSetUniformityCorrectionAllGain ( );
    virtual ~NetCmdSetUniformityCorrectionAllGain ( );

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NetCmdSetUniformityCorrectionAllGain.h ----- */

