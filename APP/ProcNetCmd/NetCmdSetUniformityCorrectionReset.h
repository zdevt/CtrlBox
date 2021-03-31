/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetUniformityCorrectionReset.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/10/2017 11:05:00 AM
 *  Last Modified:  08/10/2017 11:05:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  NETCMDSETUNIFORMITYCORRECTIONRESET_INC
#define  NETCMDSETUNIFORMITYCORRECTIONRESET_INC

#include "NetCmd.h"


class NetCmdSetUniformityCorrectionReset: public NetCmd
{
  public:
    NetCmdSetUniformityCorrectionReset ( );
    virtual ~NetCmdSetUniformityCorrectionReset ( );

  public:
    virtual int HandleCmd (  vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj ( );
};

#endif   /* ----- #ifndef NetCmdSetUniformityCorrectionReset.h ----- */
