/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetBoardState.h
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

#ifndef  NETCMDGETBOARDSTATE_INC
#define  NETCMDGETBOARDSTATE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t boardType; /*  1 信号处理板，2 机芯控制板 */
} get_boardtype_cmd_t;

typedef struct
{
  uint32_t state;   /*  0:online; 1: offline;  2: abnormal */
} get_boardstate_t;
#pragma pack(pop)

class NetCmdGetBoardState : public NetCmd
{
  public:
    NetCmdGetBoardState ( );
    virtual ~NetCmdGetBoardState();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

