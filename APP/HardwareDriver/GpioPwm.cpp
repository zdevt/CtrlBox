/*
 * =====================================================================================
 *
 *       Filename:  GpioPwm.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年03月25日 10时15分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "GpioPwm.h"
#include "LogPrint.h"
#include "Common.h"
#include "At91GpioDev.h"
#include "GpioDefine.h"

GpioPwm* GpioPwm::GetInstance()
{
  static GpioPwm instance;
  return &instance;
}

GpioPwm::GpioPwm()
  : m_pin8 ( PWM_PIN_PB8 )
  , m_pin9 ( PWM_PIN_PB9 )
{

}

GpioPwm::~GpioPwm()
{
}

int GpioPwm::Init()
{
  //#ifdef TEST_PWM
  AT91SetGpioOutput ( m_pin8, 0 );
  AT91SetGpioOutput ( m_pin9, 0 );
  //#endif
  return 0;
}

void GpioPwm::Start()
{
  //#ifdef TEST_PWM
  AT91SetGpioOutput ( m_pin8, 1 );
  usleep ( 500 * 1000 );
  AT91SetGpioOutput ( m_pin8, 0 );
  //#endif
}

void GpioPwm::Stop()
{
  //#ifdef TEST_PWM
  AT91SetGpioOutput ( m_pin8, 0 );
  usleep ( 100 * 1000 );
  AT91SetGpioOutput ( m_pin9, 0 );
  //#endif
}

void GpioPwm::Out()
{
  //#ifdef TEST_PWM
  AT91SetGpioOutput ( m_pin8, 0 );
  usleep ( 100 * 1000 );
  AT91SetGpioOutput ( m_pin9, 1 );
  //#endif
}

void GpioPwm::In()
{
  //#ifdef TEST_PWM
  AT91SetGpioOutput ( m_pin8, 1 );
  usleep ( 100 * 1000 );
  AT91SetGpioOutput ( m_pin9, 0 );
  //#endif
}
