/*
 * =====================================================================================
 *
 *       Filename:  NetCmdVerMfg.h
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

#ifndef  NETCMDVERMFG_INC
#define  NETCMDVERMFG_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t iType;
} mfg_type_t;

typedef struct
{
  int8_t date[12];
  int8_t vender[16];
  int8_t seqnum[16];
} mfg_version_t;
#pragma pack(pop)

class NetCmdVerMfg : public NetCmd
{
  public:
    NetCmdVerMfg (  );
    virtual ~NetCmdVerMfg();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );
    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

