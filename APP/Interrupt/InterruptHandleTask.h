/*
 * =====================================================================================
 *
 *       Filename:  InterruptHandleTask.h
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
#ifndef  INTERRUPTHANDLETASK_INC
#define  INTERRUPTHANDLETASK_INC

#include <queue>
#include <vector>
#include <pthread.h>
#include <semaphore.h>
#include <memory>
#include <unistd.h>


class InterruptHandleTask
{
  private:
    InterruptHandleTask();
    ~InterruptHandleTask();

  public:
    static InterruptHandleTask* GetInstance();

  public:
    void _HandleTask( );
    static void* HandleTask ( void* p );

  private:
    bool GetRunFlag();
    void SetRunFlag ( bool flag );

  private:
    bool m_runFlag;
    sem_t m_sem;
    pthread_t m_tid;
    static pthread_mutex_t m_mutex;
};

#endif   /* ----- #ifndef InterruptHandleTask.h ----- */

