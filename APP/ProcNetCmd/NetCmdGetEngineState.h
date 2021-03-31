/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetEngineState.h
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

#ifndef  NETCMDGETENGINESTATE_INC
#define  NETCMDGETENGINESTATE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t state; /*  0: off; 1: on  */
} get_engine_state_t;
#pragma pack(pop)

class NetCmdGetEngineState : public NetCmd
{
  public:
    NetCmdGetEngineState (  );
    virtual ~NetCmdGetEngineState();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );
    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

