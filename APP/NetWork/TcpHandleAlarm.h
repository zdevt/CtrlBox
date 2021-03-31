/*
 * =====================================================================================
 *
 *       Filename:  TcpHandleAlarm.h
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

#ifndef  TCPHANDLEALARM_INC
#define  TCPHANDLEALARM_INC

#include <memory>
#include <vector>

#include "TcpHandle.h"


class TcpHandleAlarm : public TcpHandle
{
  public:
    TcpHandleAlarm ( );
    virtual ~TcpHandleAlarm();

  public:
    virtual int ProcCmd ( int fd, char* buffer, int len );

  public:
    static std::shared_ptr<TcpHandle> GetObj (  );
};

#endif   /* ----- #ifndef TCPLINK_INC  ----- */

