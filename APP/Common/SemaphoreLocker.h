/*
 * =====================================================================================
 *
 *       Filename:  SemaphoreLocker.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  8/10/2016 05:02:44 PM HKT
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  SEMAPHORELOCKER_INC
#define  SEMAPHORELOCKER_INC

#include <semaphore.h>
#include <errno.h>
#include <unistd.h>

#include "LogPrint.h"

class SemLocker
{
  public:
    SemLocker ( sem_t* sem ) : m_sem ( sem )
    {
      Wait ( m_sem );
    }

    ~SemLocker()
    {
      Post ( m_sem );
    }
  private:
    void Wait ( sem_t* sem )
    {
      if ( sem )
      {
        //sem_wait ( sem );
        #if 1

        while ( ( sem_trywait ( sem ) == -1 ) && errno == EAGAIN )
        {
          sleep ( 1 );
          //PRINT_LOG2 ( "sem_trywait!!!!!\n" );
        }

        #endif
      }
    }

    void Post ( sem_t* sem )
    {
      if ( sem )
      {
        sem_post ( sem );
      }
    }

  private:
    sem_t* m_sem;

};
#endif   /* ----- #ifndef LOCKER_INC  ----- */

