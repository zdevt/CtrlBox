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

#include "Network.h"
#include "Common.h"

#define HEARTBEAT_REMOTE_PORT     (7001)

class HeartBeatAdmin
{
  public:
    HeartBeatAdmin();
    ~HeartBeatAdmin();

    int Init();
    int DeInit();
    int _Task();
    int _Task2();

  private:
    static void* HeartBeatTask ( void* p );
    static void* RecvBroadCastTask ( void* p  );

  private:
    int m_heartBeatServerPort;
    int m_heartBeatServerListenSock;

    int m_heartBeatSock;
    sockaddr_in m_heartBeatAddr;

    int m_SendBroadcastSock;
    sockaddr_in m_SendBroadcastAddr;
    int m_udpRemoteport;

    int m_udpRecvBroadcastSock;

    int m_udpServerPort;

    pthread_t m_tid;
};

#endif

