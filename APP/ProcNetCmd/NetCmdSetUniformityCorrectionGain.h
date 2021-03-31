/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetUniformityCorrectionGain.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/10/2017 11:11:11 AM
 *  Last Modified:  08/10/2017 11:11:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  NETCMDSETUNIFORMITYCORRECTIONGAIN_INC
#define  NETCMDSETUNIFORMITYCORRECTIONGAIN_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t  level;
  uint8_t  color;
  uint8_t  x;
  uint8_t  y;
  uint16_t gain;
} set_ucgain_t;
#pragma pack(pop)

class NetCmdSetUniformityCorrectionGain: public NetCmd
{
  public:
    NetCmdSetUniformityCorrectionGain ( );
    virtual ~NetCmdSetUniformityCorrectionGain ( );

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NetCmdSetUniformityCorrectionGain.h ----- */
