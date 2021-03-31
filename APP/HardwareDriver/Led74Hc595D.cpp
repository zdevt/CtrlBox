/*
 * =====================================================================================
 *
 *       Filename:  Led74Hc595D.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  10/17/2015 01:15:49 PM
 *  Last Modified:  10/17/2015 01:15:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <unistd.h>

#include "Led74Hc595D.h"
#include "At91GpioDev.h"

mapStrUint8_t Led74Hc595D::m_mapStrUint8 =
{
  {"0", 0x3f}, /*  主程序启动 */
  {"0.", 0xbf},

  {"1", 0x06}, /*  控制盒初始化 */
  {"1.", 0x86},

  {"2", 0x5b}, /*  开机打开电源 */
  {"2.", 0xdb},

  {"3", 0x4f}, /*  FPGA 加载 */
  {"3.", 0xcf},

  {"4", 0x66}, /*  FPGA DDR INIT */
  {"4.", 0xe6},

  {"5", 0x6d}, /*  开机完成 */
  {"5.", 0xed},

  {"6", 0x7d},
  {"6.", 0xfd},

  {"7", 0x07},
  {"7.", 0x87},

  {"8", 0x7f},
  {"8.", 0xff},

  {"9", 0x6f},
  {"9.", 0xef},

  {"A", 0x77},
  {"A.", 0xf7},

  {"B", 0x7c},
  {"B.", 0xfc},

  {"C", 0x39},
  {"C.", 0xb9},

  {"D", 0x5e},
  {"D.", 0xde},

  {"E", 0x79},
  {"E.", 0xf9},

  {"F", 0x71},
  {"F.", 0xf1}, /*  控制板风扇异常 */

  {"P", 0xe3},
  {"P.", 0xf3}, /*  使用期限到达 */

  {".",  0x80}, /*  设备待机 */
  {"x0", 0x5c}, /*  正常工作 */
};

Led74Hc595D* Led74Hc595D::GetInstance()
{
  static Led74Hc595D instance;
  return &instance;
}

bool Led74Hc595D::Disp ( std::string c )
{
  auto iter = m_mapStrUint8.find ( c );

  if ( iter != m_mapStrUint8.end() )
  {
    GetInstance()->WriteData ( iter->second );
    return true;
  }

  return false;
}

Led74Hc595D::Led74Hc595D()
{
  AT91SetGpioOutput ( DATA, 0 );
  AT91SetGpioOutput ( SCLK, 0 );
  AT91SetGpioOutput ( STROBE, 0 );
  AT91SetGpioOutput ( ON_OFF, 0 );

  WriteData ( 0x0 );
}

Led74Hc595D::~Led74Hc595D()
{

}

void Led74Hc595D::Delay ( int32_t ims )
{
  for ( int i = 0; i < 0x100 * ims; ++i );
}

void Led74Hc595D::SetPinLevel ( uint32_t dwPin, uint8_t byLevel )
{
  At91SetGpioValue ( dwPin, byLevel );
}

void Led74Hc595D::WriteOneBit ( uint8_t byBit )
{
  SetPinLevel ( DATA, ( byBit & 0x80 ) ? HIGH : LOW );

  SetPinLevel ( SCLK, LOW );
  Delay ( 10 );
  SetPinLevel ( SCLK, HIGH );
  Delay ( 10 );
}

void Led74Hc595D::SetStrobePulse ( void )
{
  SetPinLevel ( STROBE, LOW );
  Delay ( 10 );
  SetPinLevel ( STROBE, HIGH );
  Delay ( 40 );
  SetPinLevel ( STROBE, LOW );
}

void Led74Hc595D::WriteData ( uint8_t Data )
{
  int i;

  /*Write uint8_t*/
  for ( i = 0; i < 8; i++ )
  {
    WriteOneBit ( Data );
    Data <<= 1;
  }

  /*锁存脉冲*/
  SetStrobePulse();

  SetPinLevel ( DATA, LOW );
  SetPinLevel ( SCLK, LOW );
  SetPinLevel ( STROBE, LOW );
}

