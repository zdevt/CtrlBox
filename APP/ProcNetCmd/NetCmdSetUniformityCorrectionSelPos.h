/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetUniformityCorrectionSelPos.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/10/2017 10:59:43 AM
 *  Last Modified:  08/10/2017 10:59:43 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  NETCMDSETUNIFORMITYCORRECTIONSELPOS_INC
#define  NETCMDSETUNIFORMITYCORRECTIONSELPOS_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t x;
  uint8_t y;
} set_ucselpos_t;
#pragma pack(pop)

class NetCmdSetUniformityCorrectionSelPos: public NetCmd
{
  public:
    NetCmdSetUniformityCorrectionSelPos ( );
    virtual ~NetCmdSetUniformityCorrectionSelPos ( );

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NetCmdSetUniformityCorrectionSelPos.h ----- */
