/*
 * =====================================================================================
 *
 *       Filename:  HardwareMutex.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/10/2015 08:18:08 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include "HardwareMutex.h"
#include "At91GpioDev.h"
#include "FpgaDev.h"
#include "I2cBusInterface.h"
#include "SpiBusInterface.h"

mapIoDevMutex_t HardwareMutex::m_mapIoDevMutex =
{
  { I2C_BUS_0_NAME,     PTHREAD_MUTEX_INITIALIZER},
  { I2C_BUS_1_NAME,     PTHREAD_MUTEX_INITIALIZER},
  { I2C_BUS_2_NAME,     PTHREAD_MUTEX_INITIALIZER},
  { I2C_BUS_3_NAME,     PTHREAD_MUTEX_INITIALIZER},
  { I2C_BUS_4_NAME,     PTHREAD_MUTEX_INITIALIZER},
  { SPI_BUS_10_NAME,    PTHREAD_MUTEX_INITIALIZER},
  { SPI_BUS_20_NAME,    PTHREAD_MUTEX_INITIALIZER},
  { AT91GPIO_DEV_NAME,  PTHREAD_MUTEX_INITIALIZER},
  { FPGA_DEV_NAME,      PTHREAD_MUTEX_INITIALIZER},
};

pthread_mutex_t* HardwareMutex::GetMutex ( std::string devname )
{
  auto iter = m_mapIoDevMutex.find ( devname );

  if ( iter != m_mapIoDevMutex.end() )
    return & ( iter->second );

  return NULL;
}

HardwareMutex::HardwareMutex()
{
}

HardwareMutex::~HardwareMutex()
{
}

