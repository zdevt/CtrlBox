/*
 * =====================================================================================
 *
 *       Filename:  PowerOn.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/11/2015 11:09:39 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  POWERON_INC
#define  POWERON_INC

#include <stdint.h>
#include <pthread.h>

#include "Common.h"
#include "LogPrint.h"

class PowerOn
{
  private:
    explicit PowerOn();
    virtual ~PowerOn();

    static bool On();
    static bool Off();

  public:
    static bool SetOnOrOff ( uint8_t state );
    static bool GetOnOffFlag( );

    static void CheckOnOffKey( );

  private:
    static bool _SetOnOrOff ( uint8_t state );
    static void* SetOnOrOffTask ( void* p );

    static void* AfterOnTask ( void* p );

  private:
    static pthread_t m_tid;
    static pthread_mutex_t m_mutex;
    static bool flag;
};

#endif   /* ----- #ifndef PowerOn.h ----- */

