/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetTargetLuminance.h
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

#ifndef  NETCMDGETBCTARGETLUMINANCE_INC
#define  NETCMDGETBCTARGETLUMINANCE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t mask;
} get_targetluminance_cmd_t;

typedef struct
{
  uint32_t r;
  uint32_t g;
  uint32_t b;
} get_luminance_t;

typedef struct
{
  uint32_t mask;
  get_luminance_t r;
  get_luminance_t g;
  get_luminance_t b;
} get_targetluminance_t;
#pragma pack(pop)

class NetCmdGetTargetLuminance : public NetCmd
{
  public:
    NetCmdGetTargetLuminance ( );
    virtual ~NetCmdGetTargetLuminance();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

