/*
 * =====================================================================================
 *
 *       Filename:  NetCmdVerHardWare.h
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

#ifndef  NETCMDVERHARDWARE_INC
#define  NETCMDVERHARDWARE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t hwType;
} hw_type_t;

typedef struct
{
  int8_t model[MCP_MODEL_LEN];
  int8_t pcbVersion[MCP_VER_LEN];
  int8_t pcbaVersion[MCP_VER_LEN];
} hw_version_t;
#pragma pack(pop)

class NetCmdVerHardWare : public NetCmd
{
  public:
    NetCmdVerHardWare (  );
    virtual ~NetCmdVerHardWare();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );
    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

