/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDesktopCoor.h
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

#ifndef  NETCMDSETDESKTOPCOOR_INC
#define  NETCMDSETDESKTOPCOOR_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  int x;
  int y;
  int w;
  int h;
} set_desktopcoor_t;
#pragma pack(pop)

class NetCmdSetDesktopCoor : public NetCmd
{
  public:
    NetCmdSetDesktopCoor (  );
    virtual ~NetCmdSetDesktopCoor();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );
    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

