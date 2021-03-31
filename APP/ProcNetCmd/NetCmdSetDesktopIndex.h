/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDesktopIndex.h
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

#ifndef  NETCMDSETDESKTOPINDEX_INC
#define  NETCMDSETDESKTOPINDEX_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t desktopIndex;
} set_desktop_index_t;
#pragma pack(pop)

class NetCmdSetDesktopIndex : public NetCmd
{
  public:
    NetCmdSetDesktopIndex ( );
    virtual ~NetCmdSetDesktopIndex();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

