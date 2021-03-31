/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetEngineStateSerial.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/03/2018 17:13:32 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  NETCMDSETENGINESTATESERIAL_INC
#define  NETCMDSETENGINESTATESERIAL_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t state; /*  0: off; 1: on  */
} set_engine_state_serial_t;
#pragma pack(pop)

class NetCmdSetEngineStateSerial : public NetCmd
{
  public:
    NetCmdSetEngineStateSerial (  );
    virtual ~NetCmdSetEngineStateSerial();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDSETENGINESTATESERIAL_INC ----- */

