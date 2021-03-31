/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetLlcState.h
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

#ifndef  NETCMDSETLLCSTATE_INC
#define  NETCMDSETLLCSTATE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t ucType; /*  0:disable; 1:enable */
} set_llc_state_t;
#pragma pack(pop)

class NetCmdSetLlcState : public NetCmd
{
  public:
    NetCmdSetLlcState ( );
    virtual ~NetCmdSetLlcState();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

