/*
 * =====================================================================================
 *
 *       Filename:  NetCmdCreateColorTemp.h
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

#ifndef  NETCMDCREATECOLORTEMP_INC
#define  NETCMDCREATECOLORTEMP_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t colortempId;
  uint16_t red;
  uint16_t green;
  uint16_t blue;
} create_color_temp_t;
#pragma pack(pop)

class NetCmdCreateColorTemp : public NetCmd
{
  public:
    NetCmdCreateColorTemp ( );
    virtual ~NetCmdCreateColorTemp();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

