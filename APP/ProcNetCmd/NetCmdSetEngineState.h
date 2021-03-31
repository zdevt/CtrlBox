/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetEngineState.h
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

#ifndef  NETCMDSETENGINESTATE_INC
#define  NETCMDSETENGINESTATE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t state; /*  0: off; 1: on  */
  uint8_t broadcast; /* 0:  ; 1: broadcast */
} set_engine_state_t;
#pragma pack(pop)

class NetCmdSetEngineState : public NetCmd
{
  public:
    NetCmdSetEngineState (  );
    virtual ~NetCmdSetEngineState();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

