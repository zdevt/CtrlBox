/*
 * =====================================================================================
 *
 *       Filename:  TcpHandleConfig.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/21/2014 10:14:26 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   zt(),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  TCPHANDLECONFIG_INC
#define  TCPHANDLECONFIG_INC

#include <memory>
#include <vector>

#include "TcpHandle.h"
#include "CmdInterface.h"

class TcpHandleConfig : public TcpHandle
{
  public:
    TcpHandleConfig ( );
    virtual ~TcpHandleConfig();

  public:
    virtual int ProcCmd ( int fd, char* buffer, int len );
    static bool GetShowTcpDataFlag();
    static void SetShowTcpDataFlag ( bool flag );

  public:
    static std::shared_ptr<TcpHandle> GetObj (  );
    static bool m_showTcpData;
};

#endif   /* ----- #ifndef TCPLINK_INC  ----- */

