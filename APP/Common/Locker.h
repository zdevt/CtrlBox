/*
 * =====================================================================================
 *
 *       Filename:  Locker.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  10/11/2014 05:02:44 PM HKT
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  LOCKER_INC
#define  LOCKER_INC

#include <pthread.h>
#include <errno.h>

class Locker
{
  public:
    Locker ( pthread_mutex_t* mutex ) : m_mutex ( mutex )
    {
      Lock ( m_mutex );
    }

    ~Locker()
    {
      Unlock ( m_mutex );
    }
  private:
    void Lock ( pthread_mutex_t* mutex )
    {
      if ( mutex )
      {
        while ( pthread_mutex_trylock ( mutex ) != 0 && errno == EBUSY );
      }
    }

    void Unlock ( pthread_mutex_t* mutex )
    {
      if ( mutex )
      {
        while ( pthread_mutex_unlock ( mutex ) != 0 && errno == EINTR );
      }
    }

  private:
    pthread_mutex_t* m_mutex;

};
#endif   /* ----- #ifndef LOCKER_INC  ----- */

