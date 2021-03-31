/*
 * =====================================================================================
 *
 *       Filename:  I2cBusInterface.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/08/2015 01:32:25 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  I2cBUSINTERFACE_INC
#define  I2cBUSINTERFACE_INC

#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <map>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include "IoDevInterface.h"

#define I2C_BUS_0_NAME      "/dev/i2c-0"
#define I2C_BUS_1_NAME      "/dev/i2c-1"
#define I2C_BUS_2_NAME      "/dev/i2c-2"
#define I2C_BUS_3_NAME      "/dev/i2c-3"
#define I2C_BUS_4_NAME      "/dev/i2c-4"

#define DEV_TIMEOUT_NUM (0x5)
#define DEV_RETRIES_NUM (0x5)

typedef i2c_msg i2c_msg_t;
typedef i2c_rdwr_ioctl_data i2c_rdwr_ioctl_data_t;

enum
{
  I2C_SUB_ADDR_0_BIT     = 0,
  I2C_SUB_ADDR_8_BIT     = 1,
  I2C_SUB_ADDR_16_BIT    = 2,

  I2C_SUB_ADDR_MAX,
};


class I2cBusInterface
{
  private:
    I2cBusInterface ( );
    ~I2cBusInterface();

  public:
    static int WriteByte ( std::string busname, uint16_t slave, uint32_t addr, uint8_t data );
    static int ReadByte ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* data );

    static int WriteSlave ( std::string busname, uint16_t slave, uint8_t data );
    static int ReadSlave ( std::string busname, uint16_t slave, uint8_t* data );

    static int Write ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* pWrite,
                       uint32_t uiWriteLen, uint32_t uiAddrLen );

    static int Write ( int busNo, uint16_t slave, uint32_t addr, uint8_t* pWrite,
                       uint32_t uiWriteLen, uint32_t uiAddrLen );

    static int Read ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* pRead,
                      uint32_t uiReadLen, uint32_t uiAddrLen );

    static int Read ( int busNo, uint16_t slave, uint32_t addr, uint8_t* pRead,
                      uint32_t uiReadLen, uint32_t uiAddrLen );

    static std::string GetBusName ( int busNo );

  private:
    static std::map<int, std::string> m_mapNoBusName;
};


class I2cBusPower
{
  public:
    I2cBusPower ( std::string busName );
    ~I2cBusPower();

  private:
    std::string m_I2cBusName;
};

#endif   /* ----- #ifndef I2CDEV_INC  ----- */


