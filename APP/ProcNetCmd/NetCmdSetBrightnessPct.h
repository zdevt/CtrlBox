/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetBrightnessPct.h
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

#ifndef  NETCMDSETBRIGHTNESSPCT_INC
#define  NETCMDSETBRIGHTNESSPCT_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t coef;
} set_brightnesspct_t;
#pragma pack(pop)

class NetCmdSetBrightnessPct : public NetCmd
{
  public:
    NetCmdSetBrightnessPct (  );
    virtual ~NetCmdSetBrightnessPct();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

