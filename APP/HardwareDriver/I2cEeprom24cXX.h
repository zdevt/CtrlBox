/*
 * =====================================================================================
 *
 *       Filename:  I2cEeprom24cXX.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/09/2015 02:00:29 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  I2CEEPROM24CXX_INC
#define  I2CEEPROM24CXX_INC

#include <string>
#include <map>
#include "I2cEeprom.h"

typedef struct
{
  uint32_t addrLen;
  uint32_t pageSize;
  uint32_t capacity;
} eeprom_t;

typedef std::map<std::string, eeprom_t> mapstreeprom_t;


class I2cEeprom24cXX
{
  private:
    I2cEeprom24cXX ( );
    ~I2cEeprom24cXX();

  public:
    static int Write ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* pWrite,
                       uint32_t uiWriteLen, std::string devname = "24c64" );
    static int Read ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* pRead,
                      uint32_t uiReadLen, std::string devname = "24c64" );
  private:
    static mapstreeprom_t m_mapstreeprom;
};

#endif   /* ----- #ifndef I2CEEPROM_INC  ----- */

