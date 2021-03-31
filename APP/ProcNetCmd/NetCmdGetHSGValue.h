/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetHSGValue.h
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

#ifndef  NETCMDGETHSGVALUE_INC
#define  NETCMDGETHSGVALUE_INC

#include "NetCmd.h"
#include "NetCmdSetHSGValue.h"

#define get_hsg_value_t  set_hsg_value_t

#pragma pack(push)
#pragma pack(1)

#pragma pack(pop)

class NetCmdGetHSGValue : public NetCmd
{
  public:
    NetCmdGetHSGValue ( );
    virtual ~NetCmdGetHSGValue();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

