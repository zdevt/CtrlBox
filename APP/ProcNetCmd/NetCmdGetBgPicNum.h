/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetBgPicNum.h
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

#ifndef  NETCMDGETBGPICNUM_INC
#define  NETCMDGETBGPICNUM_INC

#include "NetCmd.h"

#if 0
#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t bgpicNum;
  uint32_t bgpicType[0];
} get_bgpic_num_t;
#pragma pack(pop)
#endif

class NetCmdGetBgPicNum : public NetCmd
{
  public:
    NetCmdGetBgPicNum (  );
    virtual ~NetCmdGetBgPicNum();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );
    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

