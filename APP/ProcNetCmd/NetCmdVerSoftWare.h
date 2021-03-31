/*
 * =====================================================================================
 *
 *       Filename:  NetCmdVerSoftWare.h
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

#ifndef  NETCMDVERSOFTWARE_INC
#define  NETCMDVERSOFTWARE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t swType;
} ver_software_t;

typedef struct
{
  int8_t swVersion[MCP_VER_LEN];
} sw_version_t;
#pragma pack(pop)

class NetCmdVerSoftWare : public NetCmd
{
  public:
    NetCmdVerSoftWare (  );
    virtual ~NetCmdVerSoftWare();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );
    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

