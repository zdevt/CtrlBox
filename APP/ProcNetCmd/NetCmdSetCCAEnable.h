/* * =====================================================================================
 *
 *       Filename:  NetCmdSetCCAEnable.h
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

#ifndef  NETCMDSETCCAENABLE_INC
#define  NETCMDSETCCAENABLE_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t enable;
} set_cca_enable_t;
#pragma pack(pop)

class NetCmdSetCCAEnable : public NetCmd
{
  public:
    NetCmdSetCCAEnable ( );
    virtual ~NetCmdSetCCAEnable();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

