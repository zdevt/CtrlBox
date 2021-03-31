/*
 * =====================================================================================
 *
 *       Filename:  GpioPwm.h
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
#ifndef  GPIOPWM_INC
#define  GPIOPWM_INC

#include <string>
#include <pthread.h>

#define GET_GPIOPWM GpioPwm::GetInstance()

class GpioPwm
{
  private:
    GpioPwm();
    ~GpioPwm();

  public:
    static GpioPwm* GetInstance();

    int  Init();
    void Start();
    void Stop();
    void Out();
    void In();


  private:
    uint32_t m_pin8;
    uint32_t m_pin9;
    pthread_t m_tid;
};

#endif   /* ----- #ifndef GpioPwm.h ----- */

