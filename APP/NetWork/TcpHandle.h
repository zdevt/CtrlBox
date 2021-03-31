/*
 * =====================================================================================
 *
 *       Filename:  TcpHandle.h
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

#ifndef  TCPHANDLE_INC
#define  TCPHANDLE_INC

#include <memory>
#include <vector>

#include "Common.h"
#include "CommunicateProtocol.h"
#include "LogPrint.h"
#include "Network.h"

typedef std::vector<char> vecharCmd_t;

class TcpHandle
{
  public:
    TcpHandle ( );
    virtual ~TcpHandle();

  public:
    virtual int HandleConnectSocket ( int fd );
    virtual int SendData ( int fd, char* buffer, int len );
    void ShowTcpData ( const char* description, char* buffer, int len );

  private:
    virtual int RecvData ( int fd, char* buffer, int& len );
    virtual int ProcData ( int fd, char* buffer, int len );
    virtual int ProcCmd ( int fd, char* buffer, int len ) = 0;

  public:
    static std::shared_ptr<TcpHandle> GetObj (  );

  private:
    char* m_buffer;
};

#endif   /* ----- #ifndef TCPLINK_INC  ----- */

