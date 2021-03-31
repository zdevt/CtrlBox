/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetDesktopIndex.h
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

#ifndef  NETCMDGETDESKTOPINDEX_INC
#define  NETCMDGETDESKTOPINDEX_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t desktopIndex;
} get_desktop_index_t;
#pragma pack(pop)

class NetCmdGetDesktopIndex : public NetCmd
{
  public:
    NetCmdGetDesktopIndex ( );
    virtual ~NetCmdGetDesktopIndex();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

