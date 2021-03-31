/*
 * =====================================================================================
 *
 *       Filename:  I2cEeprom.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/09/2015 02:00:18 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include "I2cEeprom.h"
#include "Locker.h"
#include "HardwareMutex.h"

I2cEeprom::I2cEeprom ( )
{
}

I2cEeprom::~I2cEeprom()
{
}

int I2cEeprom::WriteEeprom ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* pWrite,
                             uint32_t uiWriteLen, uint32_t uiAddrLen, unsigned int pagesize )
{
  uint32_t uiCurrentWriteSize = 0;
  uint32_t uiTotalWritePages = 0;
  uint32_t uiLastWriteSize = 0;
  uint32_t uiAddrOffset = 0;
  int ret = -1;

  uiTotalWritePages = ( addr + uiWriteLen ) / pagesize + 1 - ( addr / pagesize );
  uiLastWriteSize = ( addr + uiWriteLen ) % pagesize;

  if ( uiTotalWritePages > 1 )
    uiCurrentWriteSize = pagesize - ( addr % pagesize );
  else
    uiCurrentWriteSize = uiWriteLen;

  Locker ( HardwareMutex::GetMutex ( busname ) );

  usleep ( 6 * 1000 );

  while ( uiTotalWritePages-- )
  {
    ret = I2cBusInterface::Write ( busname, slave, addr + uiAddrOffset, pWrite + uiAddrOffset, uiCurrentWriteSize, uiAddrLen );

    if ( ret < 0 )
      return ret;

    usleep ( 6 * 1000 );
    uiAddrOffset += uiCurrentWriteSize;

    if ( uiTotalWritePages == 1 )
      uiCurrentWriteSize = uiLastWriteSize;
    else
      uiCurrentWriteSize = pagesize;
  }

  return ret;
}


int I2cEeprom::ReadEeprom ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* pRead,
                            uint32_t uiReadLen, uint32_t uiAddrLen )
{
  Locker ( HardwareMutex::GetMutex ( busname ) );

  return I2cBusInterface::Read ( busname, slave, addr, pRead, uiReadLen, uiAddrLen );
}


