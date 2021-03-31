/*
 * =====================================================================================
 *
 *       Filename:  I2cBusInterface.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/08/2015 01:35:31 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "I2cBusInterface.h"
#include "MainboardInterface.h"
#include "LogPrint.h"

std::map<int, std::string> I2cBusInterface::m_mapNoBusName =
{
  { 0, I2C_BUS_0_NAME },
  { 1, I2C_BUS_1_NAME },
  { 2, I2C_BUS_2_NAME },
  { 3, I2C_BUS_3_NAME },
  { 4, I2C_BUS_4_NAME },
};

std::string I2cBusInterface::GetBusName ( int busNo )
{
  auto iter = m_mapNoBusName.find ( busNo );

  if ( iter != m_mapNoBusName.end() )
    return iter->second;

  return I2C_BUS_0_NAME;
}

I2cBusInterface::I2cBusInterface ( )
{

}

I2cBusInterface::~I2cBusInterface()
{

}

/* 器件地址，寄存器地址，缓冲区，读取长度，寄存器地址长度(0字节，1字节(8位寄存器地址)*/
/* 2字节(16位寄存器地址)) 器件地址直接写8位地址，不关心最后1位 */
/* 返回0为成功，其他均为失败 */
/* 本函数只处理7位器件地址 内部函数不加锁 */
int I2cBusInterface::Read ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* pRead,
                            uint32_t uiReadLen, uint32_t uiAddrLen )
{
  I2cBusPower i2cBusPower ( busname );

  i2c_rdwr_ioctl_data_t i2c_ioctl_data;
  uint32_t i = 0;
  uint32_t uiAddr = addr;

  if ( !pRead )
    return -1;

  std::vector<i2c_msg_t> vecmsg;
  std::vector<uint8_t> vechar;

  vecmsg.resize ( 2 ); /* 两条iic 消息，两个起始信号 */
  i2c_ioctl_data.nmsgs = vecmsg.size();
  i2c_ioctl_data.msgs = &vecmsg[0];

  IoDevInterface::Ioctl ( busname, I2C_TIMEOUT, DEV_TIMEOUT_NUM ); /*超时时间*/
  IoDevInterface::Ioctl ( busname, I2C_RETRIES, DEV_RETRIES_NUM ); /*重复次数*/

  i2c_ioctl_data.msgs[0].len = uiAddrLen;
  i2c_ioctl_data.msgs[0].addr = static_cast<uint8_t> ( slave >> 1 );
  i2c_ioctl_data.msgs[0].flags = 0;
  i2c_ioctl_data.msgs[0].buf = NULL;

  if ( uiAddrLen > 0 )
  {
    vechar.resize ( uiAddrLen, 0 );
    i2c_ioctl_data.msgs[0].buf = &vechar[0];
  }

  for ( i = 0; i < uiAddrLen; i++ )
    i2c_ioctl_data.msgs[0].buf[i] = reinterpret_cast<uint8_t*> ( &uiAddr ) [uiAddrLen - 1 - i];

  i2c_ioctl_data.msgs[1].len = uiReadLen;
  i2c_ioctl_data.msgs[1].addr = static_cast<uint8_t> ( slave >> 1 );
  i2c_ioctl_data.msgs[1].flags = I2C_M_RD;
  i2c_ioctl_data.msgs[1].buf = pRead;

  return IoDevInterface::Ioctl ( busname, I2C_RDWR, reinterpret_cast<unsigned long> ( &i2c_ioctl_data ) );
}

int I2cBusInterface::Read ( int busNo, uint16_t slave, uint32_t addr, uint8_t* pRead,
                            uint32_t uiReadLen, uint32_t uiAddrLen )
{
  return Read ( GetBusName ( busNo ), slave, addr, pRead, uiReadLen, uiAddrLen );
}

/* 器件地址，寄存器地址，缓冲区，读取长度，寄存器地址长度(0字节，1字节(8位寄存器地址)，*/
/* 2字节(16位寄存器地址)) 器件地址直接写8位地址，不关心最后1位 */
/* 返回0为成功，其他均为失败 */
/* 本函数只处理7位器件地址 内部函数不加锁 */
int I2cBusInterface::Write ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* pWrite,
                             uint32_t uiWriteLen, uint32_t uiAddrLen )
{
  I2cBusPower i2cBusPower ( busname );

  i2c_rdwr_ioctl_data_t i2c_ioctl_data;

  uint32_t i = 0;
  uint32_t uiAddr = addr;
  uint8_t ucSlave = static_cast<uint8_t> ( slave >> 1 );

  if ( !pWrite )
    return -1;

  IoDevInterface::Ioctl ( busname, I2C_TIMEOUT, DEV_TIMEOUT_NUM ); /*超时时间*/
  IoDevInterface::Ioctl ( busname, I2C_RETRIES, DEV_RETRIES_NUM ); /*重复次数*/

  std::vector<i2c_msg_t> vecmsg;
  std::vector<uint8_t> vechar;

  vecmsg.resize ( 1 ); /* 1条iic 消息，1个起始信号 */
  i2c_ioctl_data.nmsgs = vecmsg.size();
  i2c_ioctl_data.msgs = &vecmsg[0];

  vechar.resize ( uiWriteLen + uiAddrLen, 0 );
  i2c_ioctl_data.msgs[0].buf = &vechar[0];

  i2c_ioctl_data.msgs[0].len = vechar.size();
  i2c_ioctl_data.msgs[0].addr = ucSlave;
  i2c_ioctl_data.msgs[0].flags = 0;

  for ( i = 0; i < uiAddrLen; i++ )
    i2c_ioctl_data.msgs[0].buf[i] = reinterpret_cast<uint8_t*> ( &uiAddr ) [uiAddrLen - 1 - i];

  memcpy ( ( ( i2c_ioctl_data.msgs[0].buf ) + uiAddrLen ), pWrite, uiWriteLen );

  return IoDevInterface::Ioctl ( busname, I2C_RDWR, reinterpret_cast<unsigned long> ( &i2c_ioctl_data ) );
}

int I2cBusInterface::Write ( int busNo, uint16_t slave, uint32_t addr, uint8_t* pWrite,
                             uint32_t uiWriteLen, uint32_t uiAddrLen )
{
  return Write ( GetBusName ( busNo ), slave, addr, pWrite, uiWriteLen, uiAddrLen );
}

int I2cBusInterface::WriteByte ( std::string busname, uint16_t slave, uint32_t addr, uint8_t data )
{
  return Write ( busname, slave, addr, &data, 1, 1 );
}

int I2cBusInterface::ReadByte ( std::string busname, uint16_t slave, uint32_t addr, uint8_t* data )
{
  return Read ( busname, slave, addr, data, 1, 1 );
}

int I2cBusInterface::WriteSlave ( std::string busname, uint16_t slave, uint8_t data )
{
  return Write ( busname, slave, 0, &data, 1, 0 );
}

int I2cBusInterface::ReadSlave ( std::string busname, uint16_t slave, uint8_t* data )
{
  return Read ( busname, slave, 0, data, 1, 0 );
}

I2cBusPower::I2cBusPower ( std::string busName )
  : m_I2cBusName ( busName )
{
  GET_MBPTR->SetI2cPower ( m_I2cBusName, true );
}

I2cBusPower::~I2cBusPower()
{
  GET_MBPTR->SetI2cPower ( m_I2cBusName, false );
}

