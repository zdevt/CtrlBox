/*
 * =====================================================================================
 *
 *       Filename:  TcpAdmin.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月12日 19时45分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  TCPADMIN_INC
#define  TCPADMIN_INC

#include <map>
#include <string>
#include <list>
#include <vector>
#include <semaphore.h>
#include <pthread.h>
#include <memory>

#include "Network.h"
#include "TcpHandle.h"

typedef uint16_t port_t;
typedef int lsnSock_t;
typedef int cnctSock_t;
typedef sockaddr_in cnctAddr_t;

typedef std::vector<int> vecsocket_t;
typedef std::map<cnctSock_t, cnctAddr_t> mapCnctSockAddr_t;

typedef struct
{
  lsnSock_t lsnSock;
  mapCnctSockAddr_t mapCnctSockAddr;
} lsnCnctInfo_t;
typedef std::map<port_t, lsnCnctInfo_t> mapPortLsnCnctInfo_t;


typedef  std::shared_ptr<TcpHandle> ( *pGetTcpHandleObj_t ) ();
typedef std::map< port_t, pGetTcpHandleObj_t> mapPortCnctSockHandle_t;


#define SEND_ALARM_MSG( msg, len)       TcpAdmin::GetInstance()->SendMsgToAllLink(TCP_SERVER_ALARM_PORT,msg,len);

class TcpAdmin
{
  private:
    TcpAdmin();
    ~TcpAdmin();

  public:
    static TcpAdmin* GetInstance();

  public:
    int Start();
    int Stop();

    void SendMsgToAllLink ( port_t port, char* msg, int len );

    static pthread_mutex_t* GetTcpAdminMutex();

  private:
    static void* TcpAdminTask ( void* pObj );
    void _TcpAdminTask();

    void Init();
    void DeInit();
    void AddConnect ( port_t port, cnctSock_t cnctSock, cnctAddr_t cnctAddr );

    void SetFd ( fd_set& fds );
    void HandleFd ( fd_set& fds );
    int GetMaxFd();

    bool GetRunFlag();
    void SetRunFlag ( bool flag );

  private:
    bool m_runFlag;
    mapPortLsnCnctInfo_t m_mapPortLsnCnctInfo;
    pthread_t m_tid;
    sem_t m_sem;
    static pthread_mutex_t m_mutex;
    static mapPortCnctSockHandle_t m_mapPortCnctSockHandle;
};

#endif   /* ----- #ifndef TcpAdmin.h ----- */

