/*
 * =====================================================================================
 *
 *       Filename:  HeartBeatAdmin.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年03月25日 10时15分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  HEARTBEATADMIN_INC
#define  HEARTBEATADMIN_INC

#include <string>
#include <pthread.h>
#include <vector>

#include "Network.h"
#include "Common.h"

class HeartBeatAdmin
{
  private:
    HeartBeatAdmin();
    ~HeartBeatAdmin();

  public:
    static HeartBeatAdmin* GetInstance();

    static bool GetServerOkFlag();
    static void SetServerOkFlag ( bool flag );

  private:
    static void* HeartBeatTask ( void* p );
    bool FindCtrlServer ( std::string& serverip );
    int Init();
    int DeInit();
    int _Task();
    int RecvFrom ( int sockfd, void* vptr, ssize_t n, struct sockaddr* addr, socklen_t* len );
    int RecvAllOnce ( int sockfd, void* vptr, ssize_t n, struct sockaddr* addr, socklen_t* len );

  private:
    int m_broadcastPort;
    int m_broadcastSock;
    sockaddr_in m_broadcastAddr;

    int m_udpServerPort;
    int m_udpServerSock;
    sockaddr_in m_remoteAddr;

    int m_heartBeatServerPort;
    int m_heartBeatSock;
    sockaddr_in m_heartBeatAddr;

    bool m_runFlag;

    static bool m_serverok;
    pthread_t m_tid;
};

#endif   /* ----- #ifndef HeartBeatAdmin.h ----- */

