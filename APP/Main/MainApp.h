/*
 * =====================================================================================
 *
 *       Filename:  MainApp.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/25/2015 02:48:53 PM CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  MAINAPP_INC
#define  MAINAPP_INC

#include <semaphore.h>
#include <pthread.h>

class MainApp
{
  public:
    MainApp();
    ~MainApp();

  public:
    void Init();
    void DeInit();

  public:
    static void SetRunFlag ( bool flag );
    static bool GetRunFlag( );

  public:
    static void* MainAppTask ( void* pObj );
    void _MainAppTask();

  private:
    static bool m_runFlag;

    pthread_t m_tid;
    sem_t m_sem;
};

#endif   /* ----- #ifndef MAINAPP_INC  ----- */

