/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetEngineType.h
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

#ifndef  NETCMDGETENGINETYPE_INC
#define  NETCMDGETENGINETYPE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t type[24];
} get_engine_type_t;
#pragma pack(pop)

class NetCmdGetEngineType : public NetCmd
{
  public:
    NetCmdGetEngineType (  );
    virtual ~NetCmdGetEngineType();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );
    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

