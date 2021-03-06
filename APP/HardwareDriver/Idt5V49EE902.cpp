/*
 * =====================================================================================
 *
 *       Filename:  Idt5V49EE902.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/21/2016 02:00:18 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include "Idt5V49EE902.h"
#include "I2cBusInterface.h"
#include "OpticEngineInterface.h"

/*
 * idtArg[1] = 0 74.25M 1920x1080
 * idtArg[1] = 1 42.5M  1366x768  1360x768
 * idtArg[1] = 2 81M    1600x1200
 * idtArg[1] = 3 54M    1400x1050
 * idtArg[1] = 4 32.5M  1024x768
 */
uint8_t idtArg[] =
{
  0x01, 0x03, 0x3B, 0x3B, 0x0F, 0x04, 0x00, 0x00, 0x78, 0x00, 0x96, 0x00, 0x96, 0x96, 0x96, 0x96,
  0x19, 0x19, 0x19, 0x19, 0x19, 0x00, 0x50, 0x00, 0x50, 0x50, 0x50, 0x50, 0x32, 0x32, 0x32, 0x32,
  0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x30, 0x20, 0x40, 0x00, 0x22, 0x00, 0x22, 0x22, 0x22, 0x22,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x30, 0x00, 0x30, 0x30, 0x30, 0x30, 0x80, 0xB0, 0x90, 0x90,
  0x90, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x8F, 0x00, 0x00, 0x8F, 0x8D, 0x8B, 0x00, 0x19, 0x19, 0x0F,
  0x19, 0x00, 0x92, 0x00, 0x00, 0xA6, 0xCC, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x03, 0x00, 0xCA, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F,
  0x7F, 0x7F, 0x7F, 0x7F, 0x82, 0x85, 0x81, 0x83, 0x87, 0x7F, 0x84, 0x7F, 0x84, 0x84, 0x84, 0x84,
  0x82, 0x82, 0x82, 0x82, 0x82, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x86, 0xEE,
  0x8E, 0x86, 0x86, 0x86, 0x46, 0x76, 0x76, 0x76, 0x76, 0xB6, 0x73, 0x6D, 0x73, 0x73, 0x73, 0x73,
};


Idt5V49EE902::Idt5V49EE902 ( )
{
}

Idt5V49EE902::~Idt5V49EE902 ( )
{
}

int Idt5V49EE902::SetPll ( void* parg, std::string i2cbus )
{
  int width = 0;
  int height = 0;
  GET_ENGPTR->GetEngineRes ( width, height );

  if ( ( 1920 == width ) && ( 1080 == height ) )
    idtArg[1] = 0;
  else if ( ( 1366 == width ) && ( 768 == height ) )
    idtArg[1] = 1;
  else if ( ( 1360 == width ) && ( 768 == height ) )
    idtArg[1] = 1;
  else if ( ( 1600 == width ) && ( 1200 == height ) )
    idtArg[1] = 2;
  else if ( ( 1400 == width ) && ( 1050 == height ) )
    idtArg[1] = 3;
  else if ( ( 1024 == width ) && ( 768 == height ) )
    idtArg[1] = 4;


  #if 0
  const int LEN_ONCE = 1;

  for ( uint32_t i = 0; i < sizeof ( idtArg ) / sizeof ( idtArg[0] ); i += LEN_ONCE )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "size=%d i=%d\n", sizeof ( idtArg ), i );
    I2cBusInterface::Write ( i2cbus, IDT5V49_SLAVE, i, &idtArg[i], LEN_ONCE, 0x2 );
    usleep ( 1 * 1000 );
  }

  #else
  I2cBusInterface::Write ( i2cbus, IDT5V49_SLAVE, 0, &idtArg[0], sizeof ( idtArg ), 0x2 );
  usleep ( 3 * 1000 * 1000 );
  #endif

  return 0;
}

