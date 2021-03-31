/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetUniformityCorrectionAllGain.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/10/2017 02:05:50 PM
 *  Last Modified:  08/10/2017 02:05:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  NETCMDGETUNIFORMITYCORRECTIONALLGAIN_INC
#define  NETCMDGETUNIFORMITYCORRECTIONALLGAIN_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t level;
  uint32_t gainNum;
} get_ucallgain_t;
#pragma pack(pop)

class NetCmdGetUniformityCorrectionAllGain: public NetCmd
{
  public:
    NetCmdGetUniformityCorrectionAllGain ( );
    virtual ~NetCmdGetUniformityCorrectionAllGain ( );

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NetCmdGetUniformityCorrectionAllGain.h ----- */

