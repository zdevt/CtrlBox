/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetHardWareReversion.h
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

#ifndef 	NETCMDSETHARDWAREREVERSION_INC
#define  	NETCMDSETHARDWAREREVERSION_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t hwType;
  int8_t model[MCP_MODEL_LEN];
  int8_t pcbVersion[MCP_VER_LEN];
  int8_t pcbaVersion[MCP_VER_LEN];
} set_hardwarereversion_t;
#pragma pack(pop)

class NetCmdSetHardWareReversion : public NetCmd
{
  public:
    NetCmdSetHardWareReversion (  );
    virtual ~NetCmdSetHardWareReversion();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );
    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDSETHARDWAREREVERSION_INC ----- */

