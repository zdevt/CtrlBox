/*
 * =====================================================================================
 *
 *       Filename:  MainboardDefault.cpp
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

#include <unistd.h>

#include "MainboardDefault.h"
#include "At91GpioDev.h"
#include "FpgaTestPic.h"
#include "PowerSupplyDefault.h"
#include "Ics307.h"

std::shared_ptr<Mainboard> MainboardDefault::GetObj ( std::string mainboardName )
{
  return std::make_shared<MainboardDefault> ( mainboardName );
}

MainboardDefault::MainboardDefault ( std::string mainboardName )
  : Mainboard ( mainboardName )
{

}

MainboardDefault::~MainboardDefault()
{
  DeInit();
}

bool MainboardDefault::Open()
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "\n" );
  FpgaLoad ( );
  FpgaRegSet ( FPGA_DESKTOP_REG, 0x6 ); /*  black  */

  while ( ! ( ( 1 << 2 ) & FpgaRegGet ( 0x5 ) ) )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "\n" );
    sleep ( 1 );
  }

  FpgaTestPic::WriteBmpUserDef ( "/app/user_def_0.bmp", 0 );
  FpgaTestPic::WriteBmpUserDef ( "/app/user_def_1.bmp", 1 );
  FpgaTestPic::WriteBmpUserDef ( "/app/user_def_2.bmp", 2 );
  FpgaTestPic::WriteBmpUserDef ( "/app/user_def_3.bmp", 3 );
  FpgaTestPic::WriteBmpUserDef ( "/app/user_def_4.bmp", 4 );
  FpgaTestPic::WriteBmpUserDef ( "/app/user_def_5.bmp", 5 );

  GpioSetValue ( MAINBOARDDEFAULT_SYNC_ON_OFF, 1 );
  return true;
}

bool MainboardDefault::Close()
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "\n" );
  FpgaRegSet ( FPGA_DESKTOP_REG, 0x6 ); /*  black  */
  FpgaUnLoad ( );

  GpioSetValue ( MAINBOARDDEFAULT_SYNC_ON_OFF, 0 );

  PRINT_LOG ( LOG_LEVEL_NORMAL, "SetDmdReSetPin 0\n" );
  GpioSetValue ( MAINBOARDDEFAULT_DMD_RESET, 0 );
  usleep ( 3000 * 1000 );
  return true;
}

bool MainboardDefault::Init()
{
  std::string cmd;
  cmd += "modprobe FpgaMod;";
  cmd += "modprobe GpioMod;";
  //cmd += "modprobe Interrupt;";
  cmd += "sleep 1;";
  PRINT_LOG ( LOG_LEVEL_NORMAL, "Mod %s\n", cmd.c_str() );

  system ( cmd.c_str() );

  GpioSetOutput ( MAINBOARDDEFAULT_SYNC_ON_OFF, 1 );

  PRINT_LOG ( LOG_LEVEL_NORMAL, "SetDmdReSetPin 0\n" );
  GpioSetOutput ( MAINBOARDDEFAULT_DMD_RESET, 0 );

  GpioSetInput ( MAINBOARDDEFAULT_ON_OFF, 1 );

  return false;
}

bool MainboardDefault::DeInit()
{
  FpgaUnLoad();
  return false;
}

bool MainboardDefault::BlinkLed()
{
  static int blink = 0;
  blink = !blink;
  GpioSetOutput ( MAINBOARDDEFAULT_LED, blink );
  return true;
}

bool MainboardDefault::GetOnOffGpio()
{
  return GpioGetValue ( MAINBOARDDEFAULT_ON_OFF );
}

bool MainboardDefault::SetDmdReSetPin ( bool val )
{
  /*  Ture 0,false 1 */
  return GpioSetValue ( MAINBOARDDEFAULT_DMD_RESET, val ? 0 : 1 );
}

bool MainboardDefault::SetFanSpeed ( uint8_t fanid, uint32_t speed )
{
  return true;
}

bool MainboardDefault::GetFanSpeed ( uint8_t fanid, uint32_t& speed )
{
  if ( fanid == 0 )
    speed = FpgaRegGet ( FPGA_FAN1_RATE );
  else
    speed = FpgaRegGet ( FPGA_FAN2_RATE );

  speed /= 2; /*  两个脉冲一转 */
  speed *= 60; /*  转化为分钟 */

  return true;
}

int MainboardDefault::FpgaLoad ( )
{
  return FpgaDev::Load ( FPGA_RBF_FILE_NAME, FPGA_DEV_NAME );
}

int MainboardDefault::FpgaIsLoad ( )
{
  return FpgaDev::IsLoad ( );
}

int MainboardDefault::FpgaUnLoad ( )
{
  return FpgaDev::UnLoad ( FPGA_DEV_NAME );
}

int MainboardDefault::FpgaInitGpioPin ( )
{
  fpga_pin_t* p = NULL;
  return FpgaDev::InitPin ( reinterpret_cast< fpga_pin_t*> ( p ), FPGA_DEV_NAME );
}

int MainboardDefault::FpgaRegGet ( int addr )
{
  return FpgaDev::GetReg ( addr, FPGA_DEV_NAME );
}

int MainboardDefault::FpgaRegSet ( int addr, int val )
{
  return FpgaDev::SetReg ( addr, val, FPGA_DEV_NAME );
}

int MainboardDefault::FpgaDdrGetReg ( int addr )
{
  return FpgaDev::DdrGetReg ( addr, FPGA_DEV_NAME );
}

int MainboardDefault::FpgaDdrSetReg ( int addr, int val )
{
  return FpgaDev::DdrSetReg ( addr, val, FPGA_DEV_NAME );
}

int MainboardDefault::FpgaSetRegN ( void* p )
{
  return FpgaDev::SetRegN ( reinterpret_cast<fpga_datan_t*> ( p ), FPGA_DEV_NAME );
}

int MainboardDefault::FpgaDdrSetRegN ( void* p )
{
  return FpgaDev::DdrSetRegN ( reinterpret_cast<fpga_datan_t*> ( p ), FPGA_DEV_NAME );
}

int MainboardDefault::GpioSetPeriph ( uint32_t pin, int use_pullup )
{
  return At91GpioDev::SetGpioPeriph ( pin, use_pullup, AT91GPIO_DEV_NAME );
}

int MainboardDefault::GpioSetAPeriph ( uint32_t pin, int use_pullup )
{
  return At91GpioDev::SetAPeriph ( pin, use_pullup, AT91GPIO_DEV_NAME );
}

int MainboardDefault::GpioSetBPeriph ( uint32_t pin, int use_pullup )
{
  return At91GpioDev::SetBPeriph ( pin, use_pullup, AT91GPIO_DEV_NAME );
}

int MainboardDefault::GpioSetInput ( uint32_t pin, int use_pullup )
{
  return At91GpioDev::SetGpioInput ( pin, use_pullup, AT91GPIO_DEV_NAME );
}

int MainboardDefault::GpioSetOutput ( uint32_t pin, int value )
{
  return At91GpioDev::SetGpioOutput ( pin, value, AT91GPIO_DEV_NAME );
}

int MainboardDefault::GpioSetDeglitch ( uint32_t pin, int is_on )
{
  return At91GpioDev::SetDeglitch ( pin, is_on, AT91GPIO_DEV_NAME );
}

int MainboardDefault::GpioSetMultiDriver ( uint32_t pin, int is_on )
{
  return At91GpioDev::SetMultiDriver ( pin, is_on, AT91GPIO_DEV_NAME );
}

int MainboardDefault::GpioSetValue ( uint32_t pin, int value )
{
  return At91GpioDev::SetGpioValue ( pin, value, AT91GPIO_DEV_NAME );
}

int MainboardDefault::GpioGetValue ( uint32_t pin )
{
  return At91GpioDev::GetGpioValue ( pin, AT91GPIO_DEV_NAME );
}

int MainboardDefault::SetDisplayTimming ( uint32_t w, uint32_t h, void* p )
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "w=%d h=%d\n", w, h );

  if ( ( 1400 == w ) && ( 1050 == h ) )
  {
    Ics307::SetFrequency ( ICS307_FREQUENCY_54000KHZ );

    FpgaRegSet ( FPGA_REG_HS_POL_CNT_REG,         0x8070 );
    FpgaRegSet ( FPGA_REG_VS_POL_CNT_REG,         0x8003 );
    FpgaRegSet ( FPGA_REG_HS_TOTAL_DOTCNT_REG,    0x0698 );
    FpgaRegSet ( FPGA_REG_VS_TOTAL_LINECNT_REG,   0x042a );
    FpgaRegSet ( FPGA_REG_HS2DE_STCNT_REG,        0x00f0 );
    FpgaRegSet ( FPGA_REG_HS2DE_ENDCNT_REG,       0x0668 );
    FpgaRegSet ( FPGA_REG_VS2DE_STCNT_REG,        0x000e );
    FpgaRegSet ( FPGA_REG_VS2DE_ENDCNT_REG,       0x0428 );

    /*  SET 4:3  */
    FpgaRegSet ( FPGA_REG_P3L_FLAG,               0x0000 );
  }
  else if ( ( 1920 == w ) && ( 1080 == h ) )
  {
    Ics307::SetFrequency ( ICS307_FREQUENCY_74250KHZ );

    FpgaRegSet ( FPGA_REG_HS_POL_CNT_REG,         0x8014 );
    FpgaRegSet ( FPGA_REG_VS_POL_CNT_REG,         0x8005 );
    FpgaRegSet ( FPGA_REG_HS_TOTAL_DOTCNT_REG,    0x0898 );
    FpgaRegSet ( FPGA_REG_VS_TOTAL_LINECNT_REG,   0x0465 );
    FpgaRegSet ( FPGA_REG_HS2DE_STCNT_REG,        0x00a0 );
    FpgaRegSet ( FPGA_REG_HS2DE_ENDCNT_REG,       0x0820 );
    FpgaRegSet ( FPGA_REG_VS2DE_STCNT_REG,        0x0019 );
    FpgaRegSet ( FPGA_REG_VS2DE_ENDCNT_REG,       0x0451 );

    /*  SET 16:9  */
    FpgaRegSet ( FPGA_REG_P3L_FLAG,               0x0001 );
  }

  /*  show desktop */
  FpgaRegSet ( FPGA_REG_PIC_PRO_CTL,            0x4400 );

  /*  初始完fpga输出后 再启动dmd */
  PRINT_LOG ( LOG_LEVEL_NORMAL, "Wait 5S\n" );
  sleep ( 5 );

  FpgaRegSet ( FPGA_REG_DE_WIDTH,               w );
  FpgaRegSet ( FPGA_REG_DE_HEIGHT,              h );

  /*  初始完fpga输出后 再启动dmd */
  PRINT_LOG ( LOG_LEVEL_NORMAL, "SetDmdReSetPin\n" );
  SetDmdReSetPin ( false );

  return 0;
}

int MainboardDefault::SetI2cPower ( std::string busname, bool onoff )
{
  if ( I2C_BUS_0_NAME != busname )
  {
    if ( onoff )
      GpioSetOutput ( MAINBOARDDEFAULT_I2CBUS_ON_OFF, 1 );
    else
      GpioSetOutput ( MAINBOARDDEFAULT_I2CBUS_ON_OFF, 0 );
  }

  return 0;
}

std::string MainboardDefault::GetDmdI2cBus()
{
  return I2C_BUS_1_NAME;
}

bool MainboardDefault::WriteBmpFileToFpga ( std::string filename, int addr )
{
  return FpgaTestPic::WriteBmpFileToFpga ( filename, addr );
}

int MainboardDefault::SetInputSignalRectAndShow ( int x, int y, int w, int h, uint32_t hres, uint32_t vres )
{
  return 0;
}

int MainboardDefault::CheckSignalAndShow( )
{
  return 0;
}

int MainboardDefault::WriteEdid( )
{
  return 0;
}

int MainboardDefault::GetInputSignalResol ( uint32_t& w, uint32_t& h )
{
  return 0;
}

int MainboardDefault::SetInputSignalRect ( int x, int y, int w, int h )
{
  return 0;
}

int MainboardDefault::GetInputSignalRect ( int& x, int& y, int& w, int& h )
{
  return 0;
}

int MainboardDefault::SetOuputSignalRect ( int x, int y, int w, int h )
{
  return 0;
}

int MainboardDefault::GetOuputSignalRect ( int& x, int& y, int& w, int& h )
{
  return 0;
}

int MainboardDefault::SetVsHsFactorAndShow ( int ix, int iy, int iw, int ih,
    int ox, int oy, int ow, int oh )
{
  return 0;
}

