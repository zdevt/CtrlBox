/*
 * =====================================================================================
 *
 *       Filename:  InterruptRecvTask.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年09月22日 17时07分42秒
 *  Last Modified:  2015年09月22日 17时07分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  INTERRUPTRECVTASK_INC
#define  INTERRUPTRECVTASK_INC

#include <queue>
#include <vector>
#include <pthread.h>
#include <semaphore.h>
#include <memory>
#include <unistd.h>

#include "NetLink.h"

class InterruptRecvTask
{
  private:
    InterruptRecvTask();
    ~InterruptRecvTask();

  public:
    static InterruptRecvTask* GetInstance();

  public:
    void _RecvTask ( );
    static void* RecvTask ( void* p );

    bool Pop ( std::vector<char>& vechar );

  private:
    bool GetRunFlag();
    void SetRunFlag ( bool flag );
    void Push ( std::vector<char> vechar );

  private:
    NetLink m_netlink;
    bool m_runFlag;
    std::queue<std::vector<char> > m_quectorchar;
    sem_t m_sem;
    pthread_t m_tid;
    static pthread_mutex_t m_mutex;
};

#endif   /* ----- #ifndef InterruptRecvTask.h ----- */

