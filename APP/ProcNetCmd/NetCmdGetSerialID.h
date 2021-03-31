/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetSerialID.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  09/18/2017 03:52:36 PM
 *  Last Modified:  09/18/2017 03:52:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  NETCMDGETSERIALID_INC
#define  NETCMDGETSERIALID_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t exceptionNum;
  uint16_t exceptionID[0];
} get_serialid_t;
#pragma pack(pop)

class NetCmdGetSerialID: public NetCmd
{
  public:
    NetCmdGetSerialID( );
    virtual ~NetCmdGetSerialID();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NetCmdGetSerialID.h ----- */

