/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetColorTemp.h
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

#ifndef  NETCMDSETCOLORTEMP_INC
#define  NETCMDSETCOLORTEMP_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t colortempId;
} set_colortemp_t;
#pragma pack(pop)

class NetCmdSetColorTemp : public NetCmd
{
  public:
    NetCmdSetColorTemp ( );
    virtual ~NetCmdSetColorTemp();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

