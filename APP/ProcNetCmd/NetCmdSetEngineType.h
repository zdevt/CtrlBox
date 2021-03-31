/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetEngineType.h
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

#ifndef  NETCMDSETENGINETYPE_INC
#define  NETCMDSETENGINETYPE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t type[MCP_MODEL_LEN];
} set_engine_type_t;
#pragma pack(pop)

class NetCmdSetEngineType : public NetCmd
{
  public:
    NetCmdSetEngineType (  );
    virtual ~NetCmdSetEngineType();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );
    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

