/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetProjType.h
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

#ifndef  NETCMDGETPROJTYPE_INC
#define  NETCMDGETPROJTYPE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t type;
} get_projtype_t;
#pragma pack(pop)

class NetCmdGetProjType : public NetCmd
{
  public:
    NetCmdGetProjType ( );
    virtual ~NetCmdGetProjType();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

