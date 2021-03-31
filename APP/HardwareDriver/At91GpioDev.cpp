/*
 * =====================================================================================
 *
 *       Filename:  At91GpioDev.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/09/2015 04:12:03 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include "At91GpioDev.h"
#include "LogPrint.h"

std::map<std::string, uint32_t> At91GpioDev::m_pinNameMap  =
{
  { "PA0",    AT91_PIN_PA0 },
  { "PA1",    AT91_PIN_PA1 },
  { "PA2",    AT91_PIN_PA2 },
  { "PA3",    AT91_PIN_PA3 },
  { "PA4",    AT91_PIN_PA4 },
  { "PA5",    AT91_PIN_PA5 },
  { "PA6",    AT91_PIN_PA6 },
  { "PA7",    AT91_PIN_PA7 },
  { "PA8",    AT91_PIN_PA8 },
  { "PA9",    AT91_PIN_PA9 },
  { "PA10",   AT91_PIN_PA10 },
  { "PA11",   AT91_PIN_PA11 },
  { "PA12",   AT91_PIN_PA12 },
  { "PA13",   AT91_PIN_PA13 },
  { "PA14",   AT91_PIN_PA14 },
  { "PA15",   AT91_PIN_PA15 },
  { "PA16",   AT91_PIN_PA16 },
  { "PA17",   AT91_PIN_PA17 },
  { "PA18",   AT91_PIN_PA18 },
  { "PA19",   AT91_PIN_PA19 },
  { "PA20",   AT91_PIN_PA20 },
  { "PA21",   AT91_PIN_PA21 },
  { "PA22",   AT91_PIN_PA22 },
  { "PA23",   AT91_PIN_PA23 },
  { "PA24",   AT91_PIN_PA24 },
  { "PA25",   AT91_PIN_PA25 },
  { "PA26",   AT91_PIN_PA26 },
  { "PA27",   AT91_PIN_PA27 },
  { "PA28",   AT91_PIN_PA28 },
  { "PA29",   AT91_PIN_PA29 },
  { "PA30",   AT91_PIN_PA30 },
  { "PA31",   AT91_PIN_PA31 },

  { "PB0",    AT91_PIN_PB0 },
  { "PB1",    AT91_PIN_PB1 },
  { "PB2",    AT91_PIN_PB2 },
  { "PB3",    AT91_PIN_PB3 },
  { "PB4",    AT91_PIN_PB4 },
  { "PB5",    AT91_PIN_PB5 },
  { "PB6",    AT91_PIN_PB6 },
  { "PB7",    AT91_PIN_PB7 },
  { "PB8",    AT91_PIN_PB8 },
  { "PB9",    AT91_PIN_PB9 },
  { "PB10",   AT91_PIN_PB10 },
  { "PB11",   AT91_PIN_PB11 },
  { "PB12",   AT91_PIN_PB12 },
  { "PB13",   AT91_PIN_PB13 },
  { "PB14",   AT91_PIN_PB14 },
  { "PB15",   AT91_PIN_PB15 },
  { "PB16",   AT91_PIN_PB16 },
  { "PB17",   AT91_PIN_PB17 },
  { "PB18",   AT91_PIN_PB18 },
  { "PB19",   AT91_PIN_PB19 },
  { "PB20",   AT91_PIN_PB20 },
  { "PB21",   AT91_PIN_PB21 },
  { "PB22",   AT91_PIN_PB22 },
  { "PB23",   AT91_PIN_PB23 },
  { "PB24",   AT91_PIN_PB24 },
  { "PB25",   AT91_PIN_PB25 },
  { "PB26",   AT91_PIN_PB26 },
  { "PB27",   AT91_PIN_PB27 },
  { "PB28",   AT91_PIN_PB28 },
  { "PB29",   AT91_PIN_PB29 },
  { "PB30",   AT91_PIN_PB30 },
  { "PB31",   AT91_PIN_PB31 },

  { "PC0",    AT91_PIN_PC0 },
  { "PC1",    AT91_PIN_PC1 },
  { "PC2",    AT91_PIN_PC2 },
  { "PC3",    AT91_PIN_PC3 },
  { "PC4",    AT91_PIN_PC4 },
  { "PC5",    AT91_PIN_PC5 },
  { "PC6",    AT91_PIN_PC6 },
  { "PC7",    AT91_PIN_PC7 },
  { "PC8",    AT91_PIN_PC8 },
  { "PC9",    AT91_PIN_PC9 },
  { "PC10",   AT91_PIN_PC10 },
  { "PC11",   AT91_PIN_PC11 },
  { "PC12",   AT91_PIN_PC12 },
  { "PC13",   AT91_PIN_PC13 },
  { "PC14",   AT91_PIN_PC14 },
  { "PC15",   AT91_PIN_PC15 },
  { "PC16",   AT91_PIN_PC16 },
  { "PC17",   AT91_PIN_PC17 },
  { "PC18",   AT91_PIN_PC18 },
  { "PC19",   AT91_PIN_PC19 },
  { "PC20",   AT91_PIN_PC20 },
  { "PC21",   AT91_PIN_PC21 },
  { "PC22",   AT91_PIN_PC22 },
  { "PC23",   AT91_PIN_PC23 },
  { "PC24",   AT91_PIN_PC24 },
  { "PC25",   AT91_PIN_PC25 },
  { "PC26",   AT91_PIN_PC26 },
  { "PC27",   AT91_PIN_PC27 },
  { "PC28",   AT91_PIN_PC28 },
  { "PC29",   AT91_PIN_PC29 },
  { "PC30",   AT91_PIN_PC30 },
  { "PC31",   AT91_PIN_PC31 },

  { "PD0",    AT91_PIN_PD0 },
  { "PD1",    AT91_PIN_PD1 },
  { "PD2",    AT91_PIN_PD2 },
  { "PD3",    AT91_PIN_PD3 },
  { "PD4",    AT91_PIN_PD4 },
  { "PD5",    AT91_PIN_PD5 },
  { "PD6",    AT91_PIN_PD6 },
  { "PD7",    AT91_PIN_PD7 },
  { "PD8",    AT91_PIN_PD8 },
  { "PD9",    AT91_PIN_PD9 },
  { "PD10",   AT91_PIN_PD10 },
  { "PD11",   AT91_PIN_PD11 },
  { "PD12",   AT91_PIN_PD12 },
  { "PD13",   AT91_PIN_PD13 },
  { "PD14",   AT91_PIN_PD14 },
  { "PD15",   AT91_PIN_PD15 },
  { "PD16",   AT91_PIN_PD16 },
  { "PD17",   AT91_PIN_PD17 },
  { "PD18",   AT91_PIN_PD18 },
  { "PD19",   AT91_PIN_PD19 },
  { "PD20",   AT91_PIN_PD20 },
  { "PD21",   AT91_PIN_PD21 },
  { "PD22",   AT91_PIN_PD22 },
  { "PD23",   AT91_PIN_PD23 },
  { "PD24",   AT91_PIN_PD24 },
  { "PD25",   AT91_PIN_PD25 },
  { "PD26",   AT91_PIN_PD26 },
  { "PD27",   AT91_PIN_PD27 },
  { "PD28",   AT91_PIN_PD28 },
  { "PD29",   AT91_PIN_PD29 },
  { "PD30",   AT91_PIN_PD30 },
  { "PD31",   AT91_PIN_PD31 },

  { "PE0",    AT91_PIN_PE0 },
  { "PE1",    AT91_PIN_PE1 },
  { "PE2",    AT91_PIN_PE2 },
  { "PE3",    AT91_PIN_PE3 },
  { "PE4",    AT91_PIN_PE4 },
  { "PE5",    AT91_PIN_PE5 },
  { "PE6",    AT91_PIN_PE6 },
  { "PE7",    AT91_PIN_PE7 },
  { "PE8",    AT91_PIN_PE8 },
  { "PE9",    AT91_PIN_PE9 },
  { "PE10",   AT91_PIN_PE10 },
  { "PE11",   AT91_PIN_PE11 },
  { "PE12",   AT91_PIN_PE12 },
  { "PE13",   AT91_PIN_PE13 },
  { "PE14",   AT91_PIN_PE14 },
  { "PE15",   AT91_PIN_PE15 },
  { "PE16",   AT91_PIN_PE16 },
  { "PE17",   AT91_PIN_PE17 },
  { "PE18",   AT91_PIN_PE18 },
  { "PE19",   AT91_PIN_PE19 },
  { "PE20",   AT91_PIN_PE20 },
  { "PE21",   AT91_PIN_PE21 },
  { "PE22",   AT91_PIN_PE22 },
  { "PE23",   AT91_PIN_PE23 },
  { "PE24",   AT91_PIN_PE24 },
  { "PE25",   AT91_PIN_PE25 },
  { "PE26",   AT91_PIN_PE26 },
  { "PE27",   AT91_PIN_PE27 },
  { "PE28",   AT91_PIN_PE28 },
  { "PE29",   AT91_PIN_PE29 },
  { "PE30",   AT91_PIN_PE30 },
  { "PE31",   AT91_PIN_PE31 },

};

uint32_t At91GpioDev::GetPinByName ( std::string pinName )
{
  auto iter = m_pinNameMap.find ( pinName );

  if ( iter != m_pinNameMap.end() )
    return iter->second;

  return 0;
}

At91GpioDev::At91GpioDev ( )
{
}

At91GpioDev::~At91GpioDev()
{
}

int At91GpioDev::SetGpioPeriph ( uint32_t pin, int use_pullup, std::string devname )
{
  at91gpio_ioctl_t at91gpio_dev;
  at91gpio_dev.addr = pin;
  at91gpio_dev.val = use_pullup;
  return IoDevInterface::Ioctl ( devname, CMD_SET_GPIO_PERIPH, reinterpret_cast<unsigned long> ( &at91gpio_dev ) );
}

int At91GpioDev::SetAPeriph ( uint32_t pin, int use_pullup, std::string devname )
{
  at91gpio_ioctl_t at91gpio_dev;
  at91gpio_dev.addr = pin;
  at91gpio_dev.val = use_pullup;

  return IoDevInterface::Ioctl ( devname, CMD_SET_A_PERIPH, reinterpret_cast<unsigned long> ( &at91gpio_dev ) );
}

int At91GpioDev::SetBPeriph ( uint32_t pin, int use_pullup, std::string devname )
{
  at91gpio_ioctl_t at91gpio_dev;
  at91gpio_dev.addr = pin;
  at91gpio_dev.val = use_pullup;

  return IoDevInterface::Ioctl ( devname, CMD_SET_B_PERIPH, reinterpret_cast<unsigned long> ( &at91gpio_dev ) );
}

int At91GpioDev::SetGpioInput ( uint32_t pin, int use_pullup, std::string devname )
{
  at91gpio_ioctl_t at91gpio_dev;
  at91gpio_dev.addr = pin;
  at91gpio_dev.val = use_pullup;

  return IoDevInterface::Ioctl ( devname, CMD_SET_GPIO_INPUT, reinterpret_cast<unsigned long> ( &at91gpio_dev ) );
}

int At91GpioDev::SetGpioOutput ( uint32_t pin, int value, std::string devname )
{
  at91gpio_ioctl_t at91gpio_dev;
  at91gpio_dev.addr = pin;
  at91gpio_dev.val = value;

  return IoDevInterface::Ioctl ( devname, CMD_SET_GPIO_OUTPUT, reinterpret_cast<unsigned long> ( &at91gpio_dev ) );
}

int At91GpioDev::SetDeglitch ( uint32_t pin, int is_on, std::string devname )
{
  at91gpio_ioctl_t at91gpio_dev;
  at91gpio_dev.addr = pin;
  at91gpio_dev.val = is_on;

  return IoDevInterface::Ioctl ( devname, CMD_SET_DEGLITCH, reinterpret_cast<unsigned long> ( &at91gpio_dev ) );
}

int At91GpioDev::SetMultiDriver ( uint32_t pin, int is_on, std::string devname )
{
  at91gpio_ioctl_t at91gpio_dev;
  at91gpio_dev.addr = pin;
  at91gpio_dev.val = is_on;

  return IoDevInterface::Ioctl ( devname, CMD_SET_MULTI_DRIVER, reinterpret_cast<unsigned long> ( &at91gpio_dev ) );
}

int At91GpioDev::SetGpioValue ( uint32_t pin, int value, std::string devname )
{
  at91gpio_ioctl_t at91gpio_dev;
  at91gpio_dev.addr = pin;
  at91gpio_dev.val = value;

  return IoDevInterface::Ioctl ( devname, CMD_SET_GPIO_VALUE, reinterpret_cast<unsigned long> ( &at91gpio_dev ) );
}

int At91GpioDev::GetGpioValue ( uint32_t pin, std::string devname )
{
  at91gpio_ioctl_t at91gpio_dev;
  at91gpio_dev.addr = pin;

  if ( 0 == IoDevInterface::Ioctl ( devname, CMD_GET_GPIO_VALUE, reinterpret_cast<unsigned long> ( &at91gpio_dev ) ) )
    return at91gpio_dev.val;

  return -1;
}

