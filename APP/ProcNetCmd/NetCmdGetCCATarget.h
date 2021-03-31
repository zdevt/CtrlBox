/* * =====================================================================================
 *
 *       Filename:  NetCmdGetCCATarget.h
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

#ifndef  NETCMDGETCCATARGET_INC
#define  NETCMDGETCCATARGET_INC

#include "NetCmd.h"
#include "NetCmdSetCCATarget.h"

#define get_cca_target_t set_cca_target_t

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t colorIndex;
} get_cca_target_index_t;
#pragma pack(pop)

class NetCmdGetCCATarget : public NetCmd
{
  public:
    NetCmdGetCCATarget ( );
    virtual ~NetCmdGetCCATarget();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

