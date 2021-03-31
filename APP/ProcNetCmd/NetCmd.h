/*
 * =====================================================================================
 *
 *       Filename:  NetCmd.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/06/2015 03:08:00 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  NETCMD_INC
#define  NETCMD_INC

#include <unistd.h>
#include <vector>
#include <memory>

#include "CommunicateProtocol.h"
#include "OpticEngineInterface.h"

typedef std::vector<char> vechar;

class NetCmd
{
  public:
    NetCmd ( );
    virtual ~NetCmd();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp ) = 0;

    int HandleRsp ( vechar& cmd, vechar& rsp, int ret_subtype, char* rspBuffer, int rspBufferLen );
};


#endif   /* ----- #ifndef NETCMD_INC  ----- */

