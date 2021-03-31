/*
 * =====================================================================================
 *
 *       Filename:  I2cEeprom24cXX.cpp
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

#include "I2cEeprom24cXX.h"

mapstreeprom_t I2cEeprom24cXX::m_mapstreeprom =
{
  { "24c64", { 2, 0x20, 0x2000}},

};

I2cEeprom24cXX::I2cEeprom24cXX ( )
{
}

I2cEeprom24cXX::~I2cEeprom24cXX ( )
{
}

int I2cEeprom24cXX::Write ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* pWrite,
                            uint32_t uiWriteLen, std::string devname )
{
  auto iter = m_mapstreeprom.find ( devname );

  if ( iter != m_mapstreeprom.end() )
    return I2cEeprom::WriteEeprom ( busname, slave, addr, pWrite, uiWriteLen, iter->second.addrLen, iter->second.pageSize );

  return I2cEeprom::WriteEeprom ( busname, slave, addr, pWrite, uiWriteLen, 2, 0x20 );
}

int I2cEeprom24cXX::Read ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* pRead,
                           uint32_t uiReadLen, std::string devname )
{
  auto iter = m_mapstreeprom.find ( devname );

  if ( iter != m_mapstreeprom.end() )
    return I2cEeprom::ReadEeprom ( busname, slave, addr, pRead, uiReadLen, iter->second.addrLen );

  return I2cEeprom::ReadEeprom ( busname, slave, addr, pRead, uiReadLen, 2 );
}

#ifdef TEST
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <errno.h>

int main ( int argc, char* argv[] )
{
  std::vector<char> wr;
  std::vector<char> rd;
  wr.resize ( 8 * 1024, 0 );
  rd.resize ( 8 * 1024, 0 );
  std::string busname = "/dev/i2c-0";
  int ret = 0;

  for ( int i = 0; i < wr.size(); ++i )
    wr[i] = ( uint8_t ) ( i & 0xff );

  ret = I2cEeprom24cXX::Write ( busname, 0xa8, 0x0, ( unsigned char* ) ( &wr[0] ), wr.size() );

  fprintf ( stderr, "Write ret=%d %s\n", ret, strerror ( errno ) );

  ret = I2cEeprom24cXX::Read ( busname, 0xa8, 0x0, ( unsigned char* ) ( &rd[0] ), rd.size() );

  fprintf ( stderr, "read ret=%d %s\n", ret, strerror ( errno ) );

  if ( ret > 0 )
  {
    for ( int i = 0; i < rd.size(); ++i )
    {
      if ( ( i % 0x10 ) == 0  && i != 0 )
        fprintf ( stderr, "\n" );

      fprintf ( stderr, "%02x ", rd[i] );
    }

    fprintf ( stderr, "\n" );
  }

  return 0;
}

#endif
