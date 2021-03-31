/*
 * =====================================================================================
 *
 *       Filename:  NetCmdShowIpSerial.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/11/2018 10:13:32 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  NETCMDSHOWIPSERIAL_INC
#define  NETCMDSHOWIPSERIAL_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t flag;
  uint8_t range;
} show_ip_serial_t;
#pragma pack(pop)

class NetCmdShowIpSerial : public NetCmd
{
  public:
    NetCmdShowIpSerial (  );
    virtual ~NetCmdShowIpSerial();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDSHOWIPSERIAL_INC  ----- */

