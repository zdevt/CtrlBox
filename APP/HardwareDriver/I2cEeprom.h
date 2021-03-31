/*
 * =====================================================================================
 *
 *       Filename:  I2cEeprom.h
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

#ifndef  I2CEEPROM_INC
#define  I2CEEPROM_INC

#include "I2cBusInterface.h"

class I2cEeprom
{
  private:
    I2cEeprom ( );
    ~I2cEeprom();

  public:
    static int WriteEeprom ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* pWrite,
                             uint32_t uiWriteLen, uint32_t uiAddrLen = 0x2, uint32_t pagesize = 0x20 );
    static int ReadEeprom ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* pRead,
                            uint32_t uiReadLen, uint32_t uiAddrLen = 0x2 );

};

#endif   /* ----- #ifndef I2CEEPROM_INC  ----- */

