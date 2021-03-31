/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetEngineTemp.h
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

#ifndef  NETCMDGETENGINETEMP_INC
#define  NETCMDGETENGINETEMP_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  int redTemp;
  int greenTemp;
  int blueTemp;
} get_engine_temp_t;
#pragma pack(pop)

class NetCmdGetEngineTemp : public NetCmd
{
  public:
    NetCmdGetEngineTemp (  );
    virtual ~NetCmdGetEngineTemp();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );
    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

