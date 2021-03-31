/*
 * =====================================================================================
 *
 *       Filename:  PowerSupplyDefault.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/10/2015 10:33:01 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */


#include "PowerSupplyDefault.h"
#include "Led74Hc595D.h"

std::shared_ptr<PowerSupply> PowerSupplyDefault::GetObj ( std::string powerSupplyName )
{
  return std::make_shared<PowerSupplyDefault> ( powerSupplyName );
}

PowerSupplyDefault::PowerSupplyDefault ( std::string powerSupplyName )
  : PowerSupply ( powerSupplyName )
{

}

PowerSupplyDefault::~PowerSupplyDefault()
{

}

bool PowerSupplyDefault::Open()
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "\n" );
  usleep ( 100 * 1000 );
  AT91SetGpioOutput ( POWERSUPPLYDEFAULT_ON_OFF_PIN, 1 );
  usleep ( 50 * 1000 );
  AT91SetGpioOutput ( POWERSUPPLYDEFAULT_LATCH, 1 );
  usleep ( 50 * 1000 );
  AT91SetGpioOutput ( POWERSUPPLYDEFAULT_LATCH, 0 );

  usleep ( 3000 * 1000 );
  PRINT_LOG ( LOG_LEVEL_NORMAL, "\n" );

  Led74Hc595D::Disp ( "2" );
  usleep ( 100 * 1000 );
  #if 0
  /* I2cTestSet 0x1 0xf0 0x3 0x2 0xff 0xff */
  std::vector<uint8_t> vechar;
  vechar.push_back ( 0xff );
  vechar.push_back ( 0xff );
  I2cBusInterface::Write ( I2cBusInterface::GetBusName ( 1 ),
                           0xf0, 0x3, &vechar[0], vechar.size(), 2 );
  #endif

  return false;
}

bool PowerSupplyDefault::Close()
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "\n" );
  AT91SetGpioOutput ( POWERSUPPLYDEFAULT_ON_OFF_PIN, 0 );
  AT91SetGpioOutput ( POWERSUPPLYDEFAULT_LATCH, 1 );
  AT91SetGpioOutput ( POWERSUPPLYDEFAULT_LATCH, 0 );
  usleep ( 100 * 1000 );

  #if 0
  /* I2cTestSet 0x1 0xf0 0x3 0x2 0x0 0x0 */
  std::vector<uint8_t> vechar;
  vechar.push_back ( 0x00 );
  vechar.push_back ( 0x00 );
  I2cBusInterface::Write ( I2cBusInterface::GetBusName ( 1 ),
                           0xf0, 0x3, &vechar[0], vechar.size(), 2 );
  #endif
  return false;
}

bool PowerSupplyDefault::GetAll ( power_status_all_t&  power_status_all )
{
  int ret = 0;
  power_status_data_t power_status_data;

  ret = I2cBusInterface::Read ( POWERSUPPLYDEFAULT_IIC_BUS,
                                POWERSUPPLYDEFAULT_IIC_SLAVE,
                                POWERSUPPLYDEFAULT_IIC_REG_ADDR,
                                power_status_data.data,
                                10, 1 );

  uint32_t temp = 0;

  temp =  ( power_status_data.vLsb & 0x3 ) + power_status_data.vMsb * 4;
  power_status_all.voltage = ( uint32_t ) ( temp * 0.0048828 * 4.9 * 1000 );

  temp =  ( power_status_data.tLsb & 0x3 ) + power_status_data.tMsb * 4;
  power_status_all.celsius = ( uint32_t ) ( ( 3.3 - ( ( 675 - temp ) / 1500 + temp * 0.0048828 ) ) * 60 * 1000 );


  temp =  ( power_status_data.aLsb & 0x3 ) + power_status_data.aMsb * 4;
  power_status_all.ampere = ( uint32_t ) ( 0.103 * temp * 1000 );

  power_status_all.watt = ( uint32_t ) ( ( power_status_all.voltage / 1000.0 ) * ( power_status_all.ampere / 1000.0 ) * 1000 );

  if ( ret < 0 )
    return false;

  return true;
}

