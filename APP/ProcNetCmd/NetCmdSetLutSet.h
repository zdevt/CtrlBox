/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetLutSet.h
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

#ifndef  NETCMDSETLUTSET_INC
#define  NETCMDSETLUTSET_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t set;
} set_lut_set_t;
#pragma pack(pop)

class NetCmdSetLutSet : public NetCmd
{
  public:
    NetCmdSetLutSet ( );
    virtual ~NetCmdSetLutSet();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

