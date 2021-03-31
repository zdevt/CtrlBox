/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetBoardState.h
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

#ifndef  NETCMDSETBOARDSTATE_INC
#define  NETCMDSETBOARDSTATE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t boardType;
  uint8_t state;
  uint8_t broadcast;
} set_board_state_t;
#pragma pack(pop)

class NetCmdSetBoardState : public NetCmd
{
  public:
    NetCmdSetBoardState (  );
    virtual ~NetCmdSetBoardState();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

