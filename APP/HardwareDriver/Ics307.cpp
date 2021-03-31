/*
 * =====================================================================================
 *
 *       Filename:  Ics307.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月01日 22时45分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include "Ics307.h"

Ics307::Ics307()
{

}

Ics307::~Ics307()
{

}

void Ics307::Delay ( int32_t iNs )
{

}

void Ics307::WriteOneBit ( char byBit )
{
  if ( byBit & 0x80 )
    SET_GPIO_VALUE ( ICS307_DATA, ICS307_HIGH );
  else
    SET_GPIO_VALUE ( ICS307_DATA, ICS307_LOW );

  SET_GPIO_VALUE ( ICS307_SCLK, ICS307_LOW );
  Delay ( 10 );
  SET_GPIO_VALUE ( ICS307_SCLK, ICS307_HIGH );
  Delay ( 10 );
}

void Ics307::SetStrobePulse ( void )
{
  SET_GPIO_VALUE ( ICS307_STROBE, ICS307_LOW );
  Delay ( 10 );
  SET_GPIO_VALUE ( ICS307_STROBE, ICS307_HIGH );
  Delay ( 40 );
  SET_GPIO_VALUE ( ICS307_STROBE, ICS307_LOW );
}

void Ics307::WriteData ( uint32_t dwData )
{
  int i;
  uint8_t val;

  /*锁存脉冲*/
  SetStrobePulse();
  /*uint8_t 3*/
  val = ( uint8_t ) ( dwData >> 16 );

  for ( i = 0; i < 8; i++ )
  {
    WriteOneBit ( val );
    val <<= 1;
  }

  /*uint8_t 2*/
  val = ( uint8_t ) ( dwData >> 8 );

  for ( i = 0; i < 8; i++ )
  {
    WriteOneBit ( val );
    val <<= 1;
  }

  /*uint8_t 1*/
  val = ( uint8_t ) dwData;

  for ( i = 0; i < 8; i++ )
  {
    WriteOneBit ( val );
    val <<= 1;
  }

  /*锁存脉冲*/
  SetStrobePulse();
  /*所有引脚设置为低电平*/
  SET_GPIO_VALUE ( ICS307_DATA, ICS307_LOW );
  SET_GPIO_VALUE ( ICS307_SCLK, ICS307_LOW );
  SET_GPIO_VALUE ( ICS307_STROBE, ICS307_LOW );
}

void Ics307::Init ( )
{
  SET_GPIO_OUTPUT ( ICS307_DATA, 0 );
  SET_GPIO_OUTPUT ( ICS307_SCLK, 0 );
  SET_GPIO_OUTPUT ( ICS307_STROBE, 0 );
  SET_GPIO_OUTPUT ( ICS307_PDTS, 0 );
}


void Ics307::_SetFrequency ( ICS307FreqT sFreq )
{
  uint32_t val;
  Init();
  SET_GPIO_OUTPUT ( ICS307_PDTS, 1 );

  switch ( sFreq )
  {
    case ICS307_FREQUENCY_32500kHZ:
      val = ICS307_OTHER_VAL ( 0x06 ) | ICS307_OD_VAL ( 0x00 ) | ICS307_VDW_VAL ( 0x12 ) | ICS307_RDW_VAL ( 0x02 );
      break;

    case ICS307_FREQUENCY_54000KHZ:
      val = ICS307_OTHER_VAL ( 0x06 ) | ICS307_OD_VAL ( 0x07 ) | ICS307_VDW_VAL ( 0x9A ) | ICS307_RDW_VAL ( 0x17 );
      break;

    case ICS307_FREQUENCY_81000KHZ:
      val = ICS307_OTHER_VAL ( 0x06 ) | ICS307_OD_VAL ( 0x03 ) | ICS307_VDW_VAL ( 0x9A ) | ICS307_RDW_VAL ( 0x17 );
      break;

    case ICS307_FREQUENCY_42500KHZ:
      val = ICS307_OTHER_VAL ( 0x06 ) | ICS307_OD_VAL ( 0x01 ) | ICS307_VDW_VAL ( 0x4d ) | ICS307_RDW_VAL ( 0x30 );
      break;

    case ICS307_FREQUENCY_74250KHZ:
      val = ICS307_OTHER_VAL ( 0x06 ) | ICS307_OD_VAL ( 0x01 ) | ICS307_VDW_VAL ( 0x121 ) | ICS307_RDW_VAL ( 0x62 );
      break;

    default:
      return;
  }

  WriteData ( val );
}

void Ics307::SetFrequency ( uint32_t val )
{
  if ( val < ICS307_FREQUENCY_MAX )
    _SetFrequency ( static_cast< ICS307FreqT> ( val ) );
  else
  {
    Init();
    SET_GPIO_OUTPUT ( ICS307_PDTS, 1 );
    WriteData ( val );
  }
}

