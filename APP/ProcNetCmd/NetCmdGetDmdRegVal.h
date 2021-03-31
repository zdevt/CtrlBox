/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetDmdRegVal.h
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

#ifndef  NETCMDGETDMDREGVAL_INC
#define  NETCMDGETDMDREGVAL_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t subaddr;
  uint32_t readlen;
  uint32_t datalen; /*  write len */
  uint8_t data[0];
} get_dmd_reg_val_t;

typedef struct
{
  uint8_t subaddr;
  uint32_t datalen;
  uint8_t data[0];
} ret_get_dmd_reg_val_t;
#pragma pack(pop)

class NetCmdGetDmdRegVal : public NetCmd
{
  public:
    NetCmdGetDmdRegVal ( );
    virtual ~NetCmdGetDmdRegVal();

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

